

import math


bit_mapping = """
|--------|--------|--------|--------|
| Signature [0–1] |XXXXXXXXXXXXXXXXX|
| File Size [2–5]                   |
| Reserved1 [6–7] | Reserved2 [8–9] |
| Bitmap Offset [10–13]             |
|--------|--------|--------|--------|
| Info Header Size [14–17]          |
| Width (Pixels) [18–21]            |
| Height (Pixels) [22–25]           |
| Planes [26–27] | Bits/Pixel[28–29]|
| Bit Compression [30–33]           |
| Image Size (Bytes) [34–37]        |
| Horizontal Pixels/Meter [38–41]   |
| Vertical Pixels/Meter [42–45]     |
| Number Of Colors Used [46–49]     |
| Number Of Important Colors [50–53]|
|--------|--------|--------|--------|
| Color Mapping                     |
|--------|--------|--------|--------|
"""



def signature(file):
	return file[:2]


def file_size(file):
	return (file[5] << 24) + (file[4] << 16) + (file[3] << 8) + file[2]


def bitmap_offset(file):
	return (file[13] << 24) + (file[12] << 16) + (file[11] << 8) + file[10]


def info_header_size(file):
	return (file[17] << 24) + (file[16] << 16) + (file[15] << 8) + file[14]


def width(file):
	return (file[21] << 24) + (file[20] << 16) + (file[19] << 8) + file[18]


def height(file):
	return (file[25] << 24) + (file[24] << 16) + (file[23] << 8) + file[22]


def bit_planes(file):
	return (file[27] << 8) + file[26]


def bits_per_pixel(file):
	return (file[29] << 8) + file[28]


def bit_compression(file):
	return (file[33] << 24) + (file[32] << 16) + (file[31] << 8) + file[30]


def image_size(file):
	return (file[37] << 24) + (file[36] << 16) + (file[35] << 8) + file[34]


def horizontal_pixels_per_meter(file):
	return (file[41] << 24) + (file[40] << 16) + (file[39] << 8) + file[38]


def vertical_pixels_per_meter(file):
	return (file[45] << 24) + (file[44] << 16) + (file[43] << 8) + file[42]


def number_of_colors(file):
	return (file[49] << 24) + (file[48] << 16) + (file[47] << 8) + file[46]


def number_of_important_colors(file):
	return (file[53] << 24) + (file[52] << 16) + (file[51] << 8) + file[51]


def color_mapping(file):
	start = info_header_size(file) + 14
	end = bitmap_offset(file)
	return [[file[x], file[x+1], file[x+2], file[x+3]] for x in range(start, end, 4)]


def contents(file):
	start = bitmap_offset(file)
	end = file_size(file)
	bytes_per_row = int(math.ceil((bits_per_pixel(file) * width(file)) / 8))
	padded_bytes_per_row = math.ceil(bytes_per_row / 4) * 4
	print(start, end, padded_bytes_per_row)
	return [list(file[x:x+padded_bytes_per_row]) for x in range(start, end, padded_bytes_per_row)]
	# return [(file[x+3] << 24) + (file[x+2] << 16) + (file[x+1] << 8) + file[x] for x in range(start, end, 4)]


def main():
	with open("BitTest.bmp", "rb") as file:
	# with open("binary_bitmap.bmp", "rb") as file:
		file = file.read()
		print(len(file))


	print(bit_mapping)

	print(bit_mapping.split("\n")[1])
	print(bit_mapping.split("\n")[2], f"""       {signature(file).decode("utf-8")}""")
	print(bit_mapping.split("\n")[3], f"""       {file_size(file)}""")
	print(bit_mapping.split("\n")[4])
	print(bit_mapping.split("\n")[5], f"""       {bitmap_offset(file)}""")
	print(bit_mapping.split("\n")[6])
	print(bit_mapping.split("\n")[7], f"""       {info_header_size(file)}""")
	print(bit_mapping.split("\n")[8], f"""       {width(file)}""")
	print(bit_mapping.split("\n")[9], f"""       {height(file)}""")
	print(bit_mapping.split("\n")[10], f"""       {bit_planes(file)} {bits_per_pixel(file)}""")
	print(bit_mapping.split("\n")[11], f"""       {bit_compression(file)}""")
	print(bit_mapping.split("\n")[12], f"""       {image_size(file)}""")
	print(bit_mapping.split("\n")[13], f"""       {horizontal_pixels_per_meter(file)}""")
	print(bit_mapping.split("\n")[14], f"""       {vertical_pixels_per_meter(file)}""")
	print(bit_mapping.split("\n")[15], f"""       {number_of_colors(file)}""")
	print(bit_mapping.split("\n")[16], f"""       {number_of_important_colors(file)}""")
	print(bit_mapping.split("\n")[17])
	for mapping in color_mapping(file):
		print(bit_mapping.split("\n")[18], f"""       {mapping}""")
	print(bit_mapping.split("\n")[19])
	for data in contents(file):
		print(data)
		# print(bit_mapping.split("\n")[18], f"""       {mapping}""")
	print(bit_mapping.split("\n")[19])


main()
