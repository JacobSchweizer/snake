

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);

void display_debug( volatile int * const addr );

extern const uint8_t const font[128*8];
extern const uint8_t const icon[128];
extern char textbuffer[4][16];

void delay(int);
void enable_interrupt(void);

//Egna
uint8_t display[32][128]; //Human readable pixel position and activation
uint8_t oled_display[512]; //Computer readable pixel position and activation


int main(void);
void display_start();
void clear_display();
void translateToImage();
void game();
void draw_snake();
int score;
char direction;

typedef struct {   // Structure declaration
  int x;           
  int y;      
}snake_part;

typedef struct {   // Structure declaration
  int x;           
  int y;      
}coordinate;


coordinate fruit_array[5];


char page;

int howToPlayCount;



int snake_length;
snake_part snake_array[100];
