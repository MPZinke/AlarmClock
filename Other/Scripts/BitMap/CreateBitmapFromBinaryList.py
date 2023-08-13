

import math


class BitFile:
	FILE_HEADER_LEN = 14
	INFO_HEADER_LEN = 40

	def __init__(self, image: list[list[int]], color_table: list[list[int]]=2):
		self._image: list[list[bytes]] = self.__to_binary(image)
		self._width: int = len(image[0]) if len(image) else 0
		self._height: int = len(image)
		self._color_table: list[list[int]] = color_table

		bitmap_size = self.padded_bytes() * self._height
		self._data = bytes(self.FILE_HEADER_LEN + self.INFO_HEADER_LEN + len(color_table)*4 + bitmap_size)

		self.signature("BM")
		self.file_size(len(self._data))
		self.bitmap_offset(BitFile.FILE_HEADER_LEN + BitFile.INFO_HEADER_LEN + len(self._color_table)*4)
		self.info_header_size(BitFile.INFO_HEADER_LEN)
		self.width(self._width)
		self.height(self._height)
		self.bit_planes(1)
		self.bits_per_pixel(1)
		self.bit_compression(0)
		self.image_size(self._width*self._height)
		self.horizontal_pixels_per_meter(3780)
		self.vertical_pixels_per_meter(3780)
		self.number_of_colors(2)
		self.number_of_important_colors(0)
		self.color_table(self._color_table)
		self.image(self._image)


	def __setitem__(self, index: int, value: bytes):
		if(isinstance(value, int)):
			value = value.to_bytes()

		self._data = self._data[:index] + value + self._data[index+1:]


	def __to_binary(self, image: list[list[int]]):
		byte_array = []
		for row in image:
			byte_array.append([])
			value = 0

			y = 1  # Catch the instance where a list is empty
			for y, col in enumerate(row):
				if(y > 0 and y % 8 == 0):
					byte_array[-1].append(value)
					value = 0

				value |= (col << (7 - (y % 8)))

			# Add remainder of value if not caught by `if(y > 0 and y % 8 == 0):`
			if(y % 8 != 0):
				byte_array[-1].append(value)

		return byte_array


	def padded_bytes(self):
		bytes_per_row = int(math.ceil(1 * self._width / 8))  # Number of bytes used
		padded_bytes_per_row = int(math.ceil(bytes_per_row / 4) * 4)  # Number of bytes required

		return padded_bytes_per_row


	def signature(self, signature=None):
		if(signature is None):
			return self._data[:2]

		self[0] = signature[0].encode("utf-8")
		self[1] = signature[1].encode("utf-8")


	def file_size(self, file_size=None):
		if(file_size is None):
			return (self._data[5] << 24) + (self._data[4] << 16) + (self._data[3] << 8) + self._data[2]

		for x in range(4):
			self[2+x] = (file_size >> (x*8)) & 0b11111111


	def bitmap_offset(self, bitmap_offset=None):
		if(bitmap_offset is None):
			return (self._data[13] << 24) + (self._data[12] << 16) + (self._data[11] << 8) + self._data[10]

		for x in range(4):
			self[10+x] = (bitmap_offset >> (x*8)) & 0b11111111


	def info_header_size(self, info_header_size=None):
		if(info_header_size is None):
			return (self._data[17] << 24) + (self._data[16] << 16) + (self._data[15] << 8) + self._data[14]

		for x in range(4):
			self[x+14] = (info_header_size >> (x*8)) & 0b11111111


	def width(self, width=None):
		if(width is None):
			return (self._data[21] << 24) + (self._data[20] << 16) + (self._data[19] << 8) + self._data[18]

		for x in range(4):
			self[x+18] = (width >> (x*8)) & 0b11111111



	def height(self, height=None):
		if(height is None):
			return (self._data[25] << 24) + (self._data[24] << 16) + (self._data[23] << 8) + self._data[22]

		for x in range(4):
			self[x+22] = (height >> (x*8)) & 0b11111111


	def bit_planes(self, bit_planes=None):
		if(bit_planes is None):
			return (self._data[27] << 8) + self._data[26]

		for x in range(2):
			self[x+26] = (bit_planes >> (x*8)) & 0b11111111


	def bits_per_pixel(self, bits_per_pixel=None):
		if(bits_per_pixel is None):
			return (self._data[29] << 8) + self._data[28]

		for x in range(2):
			self[x+28] = (bits_per_pixel >> (x*8)) & 0b11111111


	def bit_compression(self, bit_compression=None):
		if(bit_compression is None):
			return (self._data[33] << 24) + (self._data[32] << 16) + (self._data[31] << 8) + self._data[30]

		for x in range(4):
			self[x+30] = (bit_compression >> (x*8)) & 0b11111111


	def image_size(self, image_size=None):
		if(image_size is None):
			return (self._data[37] << 24) + (self._data[36] << 16) + (self._data[35] << 8) + self._data[34]

		for x in range(4):
			self[x+34] = (image_size >> (x*8)) & 0b11111111


	def horizontal_pixels_per_meter(self, horizontal_pixels_per_meter=None):
		if(horizontal_pixels_per_meter is None):
			return (self._data[41] << 24) + (self._data[40] << 16) + (self._data[39] << 8) + self._data[38]

		for x in range(4):
			self[x+38] = (horizontal_pixels_per_meter >> (x*8)) & 0b11111111


	def vertical_pixels_per_meter(self, vertical_pixels_per_meter=None):
		if(vertical_pixels_per_meter is None):
			return (self._data[45] << 24) + (self._data[44] << 16) + (self._data[43] << 8) + self._data[42]

		for x in range(4):
			self[x+42] = (vertical_pixels_per_meter >> (x*8)) & 0b11111111


	def number_of_colors(self, number_of_colors=None):
		if(number_of_colors is None):
			return (self._data[49] << 24) + (self._data[48] << 16) + (self._data[47] << 8) + self._data[46]

		for x in range(4):
			self[x+46] = (number_of_colors >> (x*8)) & 0b11111111


	def number_of_important_colors(self, number_of_important_colors=None):
		if(number_of_important_colors is None):
			return (self._data[53] << 24) + (self._data[52] << 16) + (self._data[51] << 8) + self._data[50]

		for x in range(4):
			self[x+50] = (number_of_important_colors >> (x*8)) & 0b11111111


	def color_table(self, color_table: list[list[int]]=None):
		start = self.info_header_size() + BitFile.FILE_HEADER_LEN
		end = self.bitmap_offset()

		if(color_table is None):
			return [[self._data[x], self._data[x+1], self._data[x+2], self._data[x+3]] for x in range(start, end, 4)]

		for x, table in enumerate(color_table):
			for y, color in enumerate(table):
				self[start + 4*x + y] = color


	def image(self, image: list[list[bytes]]=None):
		start = self.bitmap_offset()
		end = self.file_size()
		padded_bytes_per_row = self.padded_bytes()

		if(image is None):
			return [list(self._data[x:x+padded_bytes_per_row]) for x in range(start, end, padded_bytes_per_row)]

		for x in range(self._height):
			for y in range(int(math.ceil(1 * self._width / 8))):
				self[self.bitmap_offset() + (x*padded_bytes_per_row) + y] = self._image[x][y]


def create_image():
	# return [[int((y // 64 % 2 == 1 and x // 64 % 2 != 1) or (y // 64 % 2 != 1 and x // 64 % 2 == 1)) for y in range(512)] for x in range(512)]
	return [
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
][::-1]


def main():
	image = create_image()
	bitfile = BitFile(image, [[0,0,0,0], [255,255,255,255]])
	with open("BitTest.bmp", "wb") as file:
		file.write(bitfile._data)


main()
