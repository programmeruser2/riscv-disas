#include <iostream>
#include <cstdint>
#include <bitset>
int16_t twoscomp_to_int(uint16_t n, int size) {
	uint16_t msb = n & (1<<(size-1)); // most significant bit (sign bit in two's complement)
	if (msb == 0) {
		return n;
	} else {
		return -(((~n) & ((1<<size)-1)) + 1);
	}
}
uint8_t get8b(uint32_t n, int shift, int nbits) {
	return (n >> shift) & ((1<<nbits)-1);
}
uint16_t get16b(uint32_t n, int shift, int nbits) {
	return (n >> shift) & ((1<<nbits)-1);
}
void opcode33(uint32_t instruction) {
	uint8_t rd = get8b(instruction, 7, 5);
}
void opcode13(uint32_t instruction) {
	uint8_t rd = get8b(instruction, 7, 5);
	uint8_t funct3 = get8b(instruction, 12, 3);
	uint8_t rs1 = get8b(instruction, 15, 5);
	uint16_t imm;
	switch (funct3) {
		case 0:
			imm = get16b(instruction, 20, 12);
			std::cout << "addi x" << (int)rd << ", x" << (int)rs1 << ", " << twoscomp_to_int(imm, 12) << "\n";
			break;
		
		default:
			std::cerr << "Unknown funct3 " << funct3 << "\n";
	}
}
int main() {
	uint8_t code[] = { 
		0x93, 0x02, 0x80, 0x3e,
		0x13, 0x81, 0x00, 0x7d,
		0x93, 0x01, 0x81, 0xc1,
		0x13, 0x82, 0x01, 0x83,
		0x93, 0x02, 0x82, 0x3e
	};
	int size = 20;
	int i = 0;
	while (i+4 <= size) {
		uint32_t instruction = code[i] 
		| (code[i+1] << 8)
		| (code[i+2] << 16)
		| (code[i+3] << 24);
		
		uint8_t opcode = get8b(instruction, 0, 7);
		switch (opcode) {
			case 0x33:
				opcode33(instruction);
				break;
			case 0x13:
				opcode13(instruction);
				break;
			default:
				std::cerr << "Unknown opcode " << std::bitset<7>(opcode) << "\n";
		}

		i += 4;
	}
}

