#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pixel {
  int r;
  int b;
  int g;
};

void clear_pixel( struct pixel * point ) {
  point->r = 0;
  point->b = 0;
  point->g = 0;
}

void setup( struct pixel image[729][729] ) {
  int i, j;
  for (i = 0; i < 729; i++) {
    for (j = 0; j < 729; j++) {
      clear_pixel(&image[i][j]);
    }
  }
}

void set_purple( struct pixel * point ) {
  point->r = 255;
  point->b = 255;
  point->g = 0;
}

void set_cyan( struct pixel * point ) {
  point->r = 0;
  point->b = 255;
  point->g = 255;
}

void set_white( struct pixel * point ) {
  point->r = 255;
  point->b = 255;
  point->g = 255;
}  

void draw_fractal( struct pixel image[729][729], int ac_len, int sub_len ) {
  if (sub_len <= 1) {
    set_white( &image[364][364] );
  }
  else {
    int offset = (ac_len - sub_len) / 2;
    int i = offset;
    int j = offset;

    //printf("made it here sub_len: %d\n", sub_len);
    for ( ; i < sub_len + offset; i++) {
      //printf("made it here");
      set_cyan( &image[j][i] );
      printf("sublen: %d (%d, %d) cyan l1\n", sub_len, j, i);
      if ( i - offset == ((sub_len) / 2) - 1 ) {
	i += 1;
	j += 1;
	sub_len -= 2;
	if (sub_len <= 1) {
	  set_purple( &image[364][364] );
	  printf("sublen: %d (%d, %d): purple main case\n", sub_len, j, i);
	  return;
	}
	for ( ; i < sub_len + offset; i++ ) {
	  set_purple( &image[j][i] );
	  printf("sublen: %d (%d, %d): purple l1\n", sub_len, j, i);
	  j += 1;
	}
	for ( ; j < sub_len + offset; j++ ) {
	  set_purple( &image[j][i] );
	  printf("sublen: %d (%d, %d): purple l2\n", sub_len, j, i);
	  i -= 1;
	}
	for ( ; i > offset + 1; i-- ) {
	  set_purple( &image[j][i] );
	  printf("sublen: %d (%d, %d): purple l3\n", sub_len, j, i);
	  j -= 1;
	}
	for ( ; j > offset + 1; j-- ) {
	  set_purple( &image[j][i] );
	  printf("sublen: %d (%d, %d): purple l4\n", sub_len, j, i);
	  i += 1;
	}
	sub_len += 2;
	i -= 1;
	j -= 1;
      }
    }
    i--;
    
    for ( ; j < sub_len + offset; j++ ) {
      set_cyan( &image[j][i] );
      printf("sublen: %d (%d, %d) cyan l2\n", sub_len, j, i);
    }
    j--;

    for ( ; i >= offset; i-- ) {
      set_cyan( &image[j][i] );
      printf("sublen: %d (%d, %d) cyan l3\n", sub_len, j, i);
    }
    i++;

    for ( ; j >= offset; j-- ) {
      set_cyan( &image[j][i] );
      printf("sublen: %d (%d, %d) cyan l4\n", sub_len, j, i);
    }

    draw_fractal(image, ac_len, (sub_len - 5) / 2);
  }
}

int main() {
  FILE * fp;
  struct pixel image[729][729];
  int h, k;

  /*
  printf("image[0][0] init val: %d %d %d \n", image[0][0].r, image[0][0].g, image[0][0].b);

  clear_pixel(&image[0][0]);
  
  printf("image[0][0] cleared val: %d %d %d \n", image[0][0].r, image[0][0].g, image[0][0].b);  
  */
  
  setup(image);

  draw_fractal( image, 729, 729 );

  fp = fopen("./image.ppm", "w");

  fputs("P3 \n729 729 \n255 \n", fp);

  fclose(fp);
  
  fp = fopen("./image.ppm", "a");

  printf("preloop\n");

  for (h = 0; h < 729; h++) {
    for (k = 0; k < 729; k++) {
      //printf("image point (%d, %d): %d %d %d \n", h, k, image[k][h].r, image[k][h].g, image[k][h].b);
      fprintf(fp, "%d %d %d \n", image[k][h].r, image[k][h].g, image[k][h].b);
    }
  }
  
  printf("made it here\n");
  fclose(fp);
  printf("done\n");
}
