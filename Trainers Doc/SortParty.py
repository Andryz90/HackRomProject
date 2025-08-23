import re

INPUT_FILE = "trainers.party"
OUTPUT_FILE = "trainers_sorted.party"

def remove_c_comments(text: str) -> str:
    return re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)

def parse_trainer_blocks(text: str):
    blocks = []
    current_block = []

    for line in text.splitlines():
        line = line.rstrip("\n")
        if line.startswith("===") and "TRAINER_" in line:
            if current_block:
                blocks.append(current_block)
            current_block = [line]
        else:
            current_block.append(line)
    if current_block:
        blocks.append(current_block)
    return blocks

def get_trainer_level(block):
    levels = []
    for line in block:
        line = line.strip()
        if line.startswith("Level:"):
            try:
                lvl = int(line.split(":", 1)[1].strip())
                levels.append(lvl)
            except ValueError:
                pass
    if levels:
        return max(levels)  # o sum(levels)/len(levels) per livello medio
    return 0

# --- MAIN ---
with open(INPUT_FILE, encoding="utf-8") as f:
    raw_text = f.read()

raw_text = remove_c_comments(raw_text)
trainer_blocks = parse_trainer_blocks(raw_text)

# Ordina in base al livello massimo dei Pokémon
trainer_blocks_sorted = sorted(trainer_blocks, key=get_trainer_level)

# Scrivi il file ordinato
with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
    for block in trainer_blocks_sorted:
        for line in block:
            f.write(line + "\n")
        f.write("\n")  # separatore tra trainer

print(f"File ordinato scritto in {OUTPUT_FILE}")
