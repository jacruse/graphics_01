#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pixel {
  int r;
  int b;
  int g;
};

void clear_pixel( struct pixel point ) {
  point.r = 0;
  point.b = 0;
  point.g = 0;
}

void setup( struct pixel image[27][27] ) {
  int i = 0;
  int j = 0;
  for (; i < 27; i++) {
    for (; j < 27; j++) {
      clear_pixel(image[i][j]);
    }
  }
}

void set_purple( struct pixel point ) {
  point.r = 256;
  point.b = 256;
  point.g = 0;
}

void set_cyan( struct pixel point ) {
  point.r = 0;
  point.b = 256;
  point.g = 256;
}

void set_white( struct pixel point ) {
  point.r = 256;
  point.b = 256;
  point.g = 256;
}  

void draw_fractal( struct pixel image[27][27], int ac_len, int sub_len ) {
  if (sub_len <= 1) {
    set_white( image[13][13] );
  }
  else {
    int offset = (ac_len - sub_len) / 2;
    int i = 0;
    int j = 0;

    //printf("made it here sub_len: %d\n", sub_len);
    for ( ; i < sub_len; i++) {
      //printf("made it here");
      set_cyan( image[offset][offset + i] );
      if (i == (sub_len / 2) + 1) {
	offset += 1;
	sub_len -= 2;
	if (sub_len == 1) {
	  set_purple( image[13][13] );
	  return;
	}
	for ( ; i < sub_len; i++ ) {
	  set_purple( image[j + offset][i + offset] );
	  j += 1;
	}
	for ( ; j < sub_len; j++ ) {
	  set_purple( image[offset + j][i + offset] );
	  i -= 1;
	}
	for ( ; i >= 0; i-- ) {
	  set_purple( image[offset + j][offset + i] );
	  j -= 1;
	}
	for ( ; j >= 0; j-- ) {
	  set_purple( image[offset + j][offset + i] );
	  i += 1;
	}
	sub_len += 2;
	offset -= 1;
      }
    }
    
    for ( ; j < sub_len; j++ ) {
      set_cyan( image[offset + j][offset + i] );
    }

    for ( ; i >= 0; i-- ) {
      set_cyan( image[offset + j][offset + i] );
    }

    for ( ; j >= 0; j-- ) {
      set_cyan( image[offset + j][offset + i] );
    }

    draw_fractal(image, ac_len, (sub_len - 5) / 2);
  }
}

int main() {
  FILE * fp;
  struct pixel image[27][27];

  draw_fractal( image, 27, 27 );

  
  fp = fopen("./image.ppm", "a");

  for (int i = 0; i < 27; i++) {
    for (int j = 0; j < 27; j++) {
      fprintf(fp, "%d %d %d \n", image[i][j].r, image[i][j].g, image[i][j].b);
    }
  }
}
