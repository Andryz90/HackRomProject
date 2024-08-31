import csv
import re
import argparse

def load_csv_data(csv_file):
    tm_data = {}
    with open(csv_file, mode='r') as file:
        reader = csv.DictReader(file, delimiter=';')
        for row in reader:
            tm_name = row['TM_Name']
            tm_data[tm_name] = {
                'description': row['description'],
                'secondaryID': row['secondaryID']
            }
    return tm_data

def split_description(description):
    """Split description into lines of at most 19 characters, including \n."""
    lines = []
    while description:
        if len(description) <= 19:
            lines.append(description)
            break
        else:
            split_index = description.rfind(' ', 0, 19)
            if split_index == -1:
                split_index = 19
            lines.append(description[:split_index])
            description = description[split_index:].lstrip()
    return lines

def format_compound_string(description):
    """Format the description into COMPOUND_STRING format."""
    lines = split_description(description)
    formatted_description = '    ' + '\n    '.join(f'"{line}"' for line in lines)
    return f'COMPOUND_STRING(\n{formatted_description}\n)'

def process_header_file(header_file, tm_data):
    try:
        with open(header_file, 'r') as file:
            file_data = file.read()

        # Find the positions of the TM section
        tm_start = file_data.find("// TM START")
        tm_end = file_data.find("// TM END")
        if tm_start == -1 or tm_end == -1:
            print("TM section not found in the header file.")
            return

        # Calculate the end position of the TM section to include "// TM END"
        tm_end_adjusted = tm_end + len("// TM END")

        # Separate the data before, within, and after the TM section
        data_before_tm_section = file_data[:tm_start].rstrip()
        tm_section = file_data[tm_start:tm_end_adjusted].strip()
        data_after_tm_section = file_data[tm_end_adjusted:].lstrip()

        # Prepare to update the TM section
        updated_tm_section = ""

        # Regex patterns
        converted_pattern = re.compile(r'\[ITEM_TM_[A-Z_]+\] =\s*{[^}]*}', re.DOTALL)
        unconverted_pattern = re.compile(r'\[(ITEM_TM\d+)\] =\s*{([^}]*)}', re.DOTALL)

        # Add already converted TM blocks to the updated section
        for match in converted_pattern.finditer(tm_section):
            updated_tm_section += match.group() + "," + "\n"

        # Process unconverted TM blocks
        for match in unconverted_pattern.finditer(tm_section):
            item_tm_name = match.group(1)
            block = match.group(2)

            # Extract the TM number and key
            tm_number = item_tm_name.replace("ITEM_TM", "")
            tm_key = f"TM{tm_number:02}"

            if tm_key in tm_data:
                desc_data = tm_data[tm_key]
                description = desc_data['description']
                secondary_id = desc_data['secondaryID']

                if "sQuestionMarksDesc" in block:
                    if description:
                        formatted_description = format_compound_string(description)
                        block = re.sub(r'(\.description\s*=\s*)sQuestionMarksDesc,', rf'\1{formatted_description},', block)
                    else:
                        # Prompt user to input description if missing
                        while True:
                            try:
                                description = input(f"Enter description for {secondary_id} ({tm_key}): ")
                                if description.strip():
                                    break
                                else:
                                    print("Description cannot be empty. Please enter a valid description.")
                            except Exception as e:
                                print(f"An error occurred while reading input: {e}")

                        formatted_description = format_compound_string(description)
                        tm_data[tm_key]['description'] = description
                        block = re.sub(r'(\.description\s*=\s*)sQuestionMarksDesc,', rf'\1{formatted_description},', block)

                block = re.sub(r'(\.secondaryId\s*=\s*)[^,]*,', rf'\1{secondary_id},', block)

                item_tm_name_replacement = f"ITEM_{desc_data['secondaryID'].replace('MOVE_', '')}"
                updated_tm_section += f'    [{item_tm_name_replacement}] = {{\n{block}}},\n'
            else:
                updated_tm_section += f'    [{item_tm_name}] = {{\n{block}}},\n'

        # Combine the sections with the updated TM section
        updated_file_data = data_before_tm_section + "\n// TM START\n" + updated_tm_section.strip() + "\n// TM END" + data_after_tm_section

        # Write the updated data back to the file
        with open(header_file, 'w') as file:
            file.write(updated_file_data)
        
        print(f"Header file '{header_file}' has been updated successfully.")

    except FileNotFoundError:
        print(f"File not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

def main(header_file, csv_file):
    tm_data = load_csv_data(csv_file)
    process_header_file(header_file, tm_data)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Update C++ header file with data from a CSV file.")
    parser.add_argument("header_file", help="Path to the C++ header file.")
    parser.add_argument("csv_file", help="Path to the CSV file with TM data.")
    
    #args = parser.parse_args()
    
    #main(args.header_file, args.csv_file)
    
    main("D:/Git Repos/HackRomProject/PokemonSourceCode/pokeemerald/src/data/items.h", "tm_data.csv")
