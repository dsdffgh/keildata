#include <reg52.h>
#include <string.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define N 16
typedef unsigned char uint8_t;

uint8_t code strip_init_left[N] = {0, 0, 0, 0, 0, 0, 0, 0, 100, 50, 25, 12, 6, 3, 1, 0};
uint8_t code strip_init_right[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 12, 25, 50, 100};
uint8_t duties[N];
uint8_t duties_left[N];
uint8_t duties_right[N];

void shift_right_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, t = buf[len-1];
    for(i = len-1; i > 0; i--) {
        buf[i] = buf[i-1];
    }
    buf[0] = t;
}
void shift_left_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, n = len-1, t = buf[0];
    for(i=0; i<n; i++) {
        buf[i] = buf[i+1];
    }
    buf[n] = t;
}
void shift_center_strip() {
    uint8_t i;
    shift_left_strip(duties_left, N);
    shift_right_strip(duties_right, N);
    for(i=0; i<N; i++) {
        duties[i] = MAX(duties_left[i], duties_right[i]);
    }
}
void update_leds(uint8_t cycle, uint8_t *values) {
    uint8_t i, j, value;
    while(cycle--) {
        for(i=0; i<100; i++) {
            value = 0;
            for(j=0; j<8; j++) {
                if (i >= values[j]) {
                    value |= (1<<j);
                }
            }
            P2 = value;
        }
    }
}
void main() {
    uint8_t i;
    while(1) {
        memcpy(duties, strip_init_right, N);
        for(i=0; i<9; i++) {
            shift_right_strip(duties, N);
            update_leds(4, duties);
        }
        memcpy(duties, strip_init_left, N);
        for(i=0; i<9; i++) {
            shift_left_strip(duties, N);
            update_leds(4, duties);
            
        }
        memcpy(duties_left, strip_init_left, N);
        memcpy(duties_right, strip_init_right, N);
        for(i=0; i<15; i++) {
            shift_center_strip();
            update_leds(4, duties);
        }
    }
}
