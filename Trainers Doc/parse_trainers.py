import csv
import os
import re

# --- Configurazione ---
INPUT_FOLDER = "./"
OUTPUT_CSV = "trainers.csv"

def normalize_pic_name(pic_str: str) -> str:
    return pic_str.strip().lower().replace(" ", "_") + ".png"

def normalize_pokemon_name(name: str) -> str:
    # Tutto lowercase, rimuove spazi, punti, apostrofi, simboli ♀♂
    return (name.lower()
                .replace(" ", "")
                .replace(".", "")
                .replace("'", "")
                .replace("♀", "f")
                .replace("♂", "m"))

def remove_c_comments(text: str) -> str:
    # Rimuove blocchi /**/
    return re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)

def parse_trainer_file(filepath: str):
    trainers = []
    current_trainer = None
    current_pokemon = None

    with open(filepath, encoding="utf-8") as f:
        raw_text = f.read()

    raw_text = remove_c_comments(raw_text)
    lines = [line.rstrip("\n") for line in raw_text.splitlines()]

    for line in lines:
        line = line.strip()

        # Nuovo trainer
        if line.startswith("===") and "TRAINER_" in line:
            if current_pokemon and current_trainer:
                current_trainer["pokemon"].append(current_pokemon)
                current_pokemon = None
            if current_trainer:
                trainers.append(current_trainer)
            current_trainer = {"name": None, "pic": None, "pokemon": []}
            current_pokemon = None
            continue

        # Nome trainer
        if line.startswith("Name:") and current_trainer:
            current_trainer["name"] = line.split(":", 1)[1].strip()
            continue

        # Pic trainer
        if line.startswith("Pic:") and current_trainer:
            pic_str = line.split(":", 1)[1].strip()
            current_trainer["pic"] = normalize_pic_name(pic_str)
            continue

        # Nuovo Pokémon (prima riga: nome specie)
        if line and not line.startswith(("Item:", "Ability:", "Level:", "-", "IVs", "EVs")) and not line.endswith("Nature") and ":" not in line:
            if current_pokemon and current_pokemon.get("lines"):
                current_trainer["pokemon"].append(current_pokemon)
            current_pokemon = {"lines": [line]}
            continue

        # Linee successive del Pokémon
        if current_pokemon is not None and line:
            current_pokemon["lines"].append(line)
            continue

    # Aggiungi ultimo Pokémon e trainer
    if current_pokemon and current_trainer and current_pokemon.get("lines"):
        current_trainer["pokemon"].append(current_pokemon)
    if current_trainer:
        trainers.append(current_trainer)

    return trainers

# --- MAIN ---
all_trainers = []
for filename in os.listdir(INPUT_FOLDER):
    if filename.endswith("trainers_sorted.party"):
        path = os.path.join(INPUT_FOLDER, filename)
        all_trainers.extend(parse_trainer_file(path))

# Ordina i trainer in base al livello del primo Pokémon
def get_first_level(trainer):
    if trainer["pokemon"]:
        for line in trainer["pokemon"][0]["lines"]:
            if line.startswith("Level:"):
                try:
                    return int(line.split(":", 1)[1].strip())
                except:
                    return 0
    return 0

all_trainers.sort(key=get_first_level)

with open(OUTPUT_CSV, "w", newline="", encoding="utf-8") as csvfile:
    # Separatore ; per locale IT
    writer = csv.writer(csvfile, delimiter=";", quoting=csv.QUOTE_MINIMAL, lineterminator="\n")

    for tr in all_trainers:
        pokes = tr.get("pokemon", [])
        n_pokes = len(pokes)

        # Calcolo righe extra massime tra i Pokémon (escludendo la riga nome specie)
        max_extra = 0
        for p in pokes:
            extra = max(0, len(p["lines"]) - 1)
            if extra > max_extra:
                max_extra = extra

        # --- Riga 1: immagini (allenatore e poi tutti i Pokémon)
        row_img = []
        if tr.get("pic"):
            trainer_img = f'=IFERROR(INDEX(\'ID Trainer Pics\'!C:C; MATCH("{tr["pic"]}"; \'ID Trainer Pics\'!A:A; 0)); "")'
        else:
            trainer_img = ""
        row_img.append(trainer_img)

        for p in pokes:
            # Rimuove item e genere dal nome del Pokémon
            poke_name = p["lines"][0].split(" @")[0]
            poke_name = re.sub(r"\s*\([mfMF]\)", "", poke_name)
            sprite_filename = normalize_pokemon_name(poke_name)
            image_formula = f'=IMAGE("https://play.pokemonshowdown.com/sprites/gen5/{sprite_filename}.png")'
            row_img.append(image_formula)
        writer.writerow(row_img)

        # --- Riga 2: nomi (allenatore e Pokémon)
        row_names = [tr.get("name") or ""]
        for p in pokes:
            row_names.append(p["lines"][0])
        writer.writerow(row_names)

        # --- Righe successive: dettagli di ciascun Pokémon sotto la sua colonna
        for k in range(max_extra):
            row = [""]
            for p in pokes:
                extra_lines = p["lines"][1:]
                row.append(extra_lines[k] if k < len(extra_lines) else "")
            writer.writerow(row)

        # Riga vuota di separazione tra trainer
        writer.writerow([])

print(f"CSV generato: {OUTPUT_CSV} — Trainer: {len(all_trainers)}")
