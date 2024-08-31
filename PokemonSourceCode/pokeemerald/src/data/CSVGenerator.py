import csv

def generate_tm_csv(input_file, output_file):
    tm_names = []
    with open(input_file, 'r') as file:
        inside_tm_section = False
        for line in file:
            line = line.strip()
            if line.startswith("#define FOREACH_TM(F)"):
                inside_tm_section = True
                continue

            if inside_tm_section:
                if line.startswith("F("):
                    # Extract the TM name by removing 'F(' from the start and ')' from the end
                    index = line.index(")")
                    tm_name = line[2:index]
                    tm_names.append(tm_name)
                elif line == "":  # Stop reading when an empty line is encountered after the TM list
                    break
    
    if not tm_names:
        print("No TM names found.")
        return

    # Generate TM data
    tm_data = []
    for i, name in enumerate(tm_names, start=1):
        tm_data.append({
            "TM_Name": f"TM{i:02}",  # Format as TM01, TM02, etc.
            "description": "",  # Leave description empty for now
            "secondaryID": f"MOVE_{name}"
        })

    # Write to CSV with semicolon as delimiter
    with open(output_file, mode='w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=["TM_Name", "description", "secondaryID"], delimiter=';')
        writer.writeheader()
        writer.writerows(tm_data)

    print(f"CSV file '{output_file}' has been generated successfully.")

# Example usage
input_file = "tms_hms.h"  # Replace with your actual file path
output_file = "tm_data.csv"
generate_tm_csv(input_file, output_file)
