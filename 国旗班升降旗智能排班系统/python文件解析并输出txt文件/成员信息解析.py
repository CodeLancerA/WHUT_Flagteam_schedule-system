import openpyxl

def parse_data(cell_data):
    info_list = cell_data.split('┋')
    name = info_list[0].strip('名称：〖').strip('〗')
    grade = info_list[1].strip('年级：〖').strip('〗')
    height = info_list[2].strip('身高：（cm）〖').strip('〗')
    unavailable_times = '\t'.join(info_list[4:])  # Skip the gender info (info_list[3])
    return f"{name}\t{grade}\t{height}\t{unavailable_times}"

def process_excel_file(file_path):
    member_info_list = []
    wb = openpyxl.load_workbook(file_path)
    sheet = wb.active

    for cell in sheet['A']:
        if cell.value is None:
            break
        member_info = parse_data(cell.value)
        member_info_list.append(member_info)

    return member_info_list

def write_to_text_file(data_list, output_file):
    with open(output_file, 'w', encoding='utf-8') as file:
        for item in data_list:
            file.write(f"{item}\n")


if __name__ == "__main__":
    excel_file_path = "队员时间表2.xlsx"
    output_file_path = "../成员时间.txt"

    member_info_list = process_excel_file(excel_file_path)
    write_to_text_file(member_info_list, output_file_path)
