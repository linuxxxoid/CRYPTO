from pygost import gost34112012256


if __name__ == '__main__':
	print(gost34112012256.new("Вельтман Лина Ярославовна".encode('utf-8')).digest().hex()[-1])
