#include "chip8_cpu.h"

void chip8_emulate_cycle(Chip8* chip8){
    //fetch opcode, memory is byte addressable, so each opcode is 2 bytes
    unint16_t opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];

    uint8_t Vx_idx = (opcode & 0x0F00) >> 8;
    uint8_t Vy_idx = (opcode & 0x0F00) >> 4;

    chip8->pc += 2;

    switch(opcode & 0xF000){

        case 0x0000:
            switch(opcode){

                //clear screen
                case 0x00E0:
                    memset(chip8->gfx, 0, sizeof(chip8->gfx));
                    break;

                //return from subroutine
                case 0x0EE:

                    break;

                //call instruction, skipping for now as not in most modern ROMs
                default:
                    break;
            }
            break;

        //jump to address
        case 0x1000:
            chip8->pc = opcode & 0x0FFF;
            break;

        //call subroutine
        case 0x2000:
            chip8->stack[chip8->sp] = chip8->pc;
            chip8->sp++;
            chip8->pc = opcode & 0x0FFF;
            break;

        //conditional skip; ie skip if Vx == NN
        case 0x3000:
            if(chip8->V[Vx_idx] == (opcode & 0x00FF)){
                chip8->pc += 2;
            }
            break;

        //conditional skip; ie skip if Vx != NN
        case 0x4000:
            if(chip8->V[Vx_idx] != (opcode & 0x00FF)){
                chip8->pc += 2;
            }
            break;

        //conditional skip; ie skip if Vx == Vy
        case 0x5000:
            if(chip8->V[Vx_idx] == chip8->V[Vy_idx]){
                chip8->pc += 2;
            }
            break;

        //sets Vx to NN
        case 0x6000:
            chip8->V[Vx_idx] = (opcode & 0x00FF);
            break;

        //adds NN to Vx
        case 0x7000:
            chip8->V[Vx_idx] += (opcode & 0x00FF);

        case 0x8000:
            switch(opcode & 0x000F){

                //sets Vx to value of Vy
                case 0x0000:
                    chip8->V[Vx_idx] = chip8->V[Vy_idx];
                    break;

                //sets Vx to Vx | Vy
                case 0x0001:
                    chip8->V[Vx_idx] |= chip8->V[Vy_idx];
                    break;

                //sets Vx to Vx & Vy
                case 0x0002:
                    chip8->V[Vx_idx] &= chip8->V[Vy_idx];
                    break;

                //sets Vx to Vx ^ Vy
                case 0x0003:
                    chip8->V[Vx_idx] ^= chip8->V[Vy_idx];
                    break;

                //sets Vx to Vx + Vy
                case 0x0004:
                    uint16_t temp = chip8->V[Vx_idx] + chip8->V[Vy_idx];
                    chip8->V[0xF] = temp>>8;
                    chip8->V[Vx_idx] = temp;
                    break;

                //sets Vx to Vx - Vy
                case 0x0005:
                    chip8->V[0xF] = chip8->V[Vx_idx] > chip8->V[Vy_idx];
                    chip8->V[Vx_idx] = chip8->V[Vx_idx] - chip8->V[Vy_idx];
                    break;

                //right shift Vx
                case 0x0006:
                    chip8->V[0xF] = chip8->V[Vx_idx] & 0x01;
                    chip8->V[Vx_idx] >>= 1;
                    break;

                //sets Vx to Vy - Vx
                case 0x0007:
                    chip8->V[0xF] = chip8->V[Vx_idx] < chip8->V[Vy_idx];
                    chip8->V[Vx_idx] =  chip8->V[Vy_idx] - chip8->V[Vx_idx];
                    break;

                //left shift Vx
                case 0x000E:
                    chip8->V[0xF] = (chip8->V[Vx_idx] & 0x80) >> 7;
                    chip8->V[Vx_idx] <<= 1;
                    break;

                //TODO add error handling?
                default:
                    break;
            }
            break;

        //conditional skip; ie skip if Vx != Vy
        case 0x9000:
            if(chip8->V[Vx_idx] != chip8->V[Vy_idx]){
                chip8->pc += 2;
            }
            break;

        //sets I to address NNN
        case 0xA000:
            chip8->I = opcode & 0x0FFF;
            break;

        //jumps to NNN plus value in V0
        case 0xB000:
            chip8->pc = (opcode & 0x0FFF) + chip8->v[0x0];
            break;

        //Vx = random number + NNN
        case 0xC000:
            chip8->V[Vx_idx] = (rand()%255) & (opcode & 0x0FFF);
            break;

        case 0xD000:
            chip8->pc = 

        case 0xE000:

        case 0xF000:
    }
}
