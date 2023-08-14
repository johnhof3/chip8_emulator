#include <cstdint>

typedef struct Chip8 {
    uint8_t memory[4096];    // Chip8 has 4K memory
    uint8_t V[16];           // CPU registers V0-VF
    uint16_t I;              // Index register
    uint16_t pc;             // Program counter
    uint8_t gfx[64 * 32];    // 2048 pixels (64x32)
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t stack[16];
    uint8_t keypad[16];
    uint16_t sp;             // Stack pointer
    uint8_t keypad[16];
    uint8_t keypad[16];
} Chip8;

void chip8_initialize(Chip8* chip8);
void chip8_load_game(Chip8* chip8, const char* filename);
void chip8_emulate_cycle(Chip8* chip8);
