#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <unistd.h>

// define MSIZE 4

#define RESET   "\033[0m"
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"

// #define BF
#define SPEED 10

struct termios original;

typedef int msize;


void printm(int* matrix, int* mask, int pos, int MSIZE) {
	char t;
	int s;
	// printf("%c\n", '0' + MSIZE);
	for (int i = 0; i < MSIZE; i++) {
		for (int k = 0; k < MSIZE; k++) {
			s = i * MSIZE + k;
			t = '0' + *(matrix + i * MSIZE + k);
			if (t == '0') {
				t = '.';		
			}
			if (pos != -1) {
				if (pos == i * MSIZE + k) {
					if (*(mask + s) == 1) {
						if (t == '.') {
							printf("%s[%s %s] ", RESET, YELLOW, RESET);
						} else {
							printf("%s[%s%c%s] ", RESET, YELLOW, t, RESET);
						}
					} else {
						printf("[%c] ", t);
					}
					
				} else {
					if (*(mask + s) == 1) {
							printf("%s", GREEN);
					}
					if (pos != (i * MSIZE + k - 1) || ((i * MSIZE + k) % MSIZE == 0)) {
						printf(" ");
					}
					printf("%c ", t);
				}
			} else {
				printf(" %c ", t);
			}
			printf("%s", RESET);
		}
		printf("\n");
	}
	// printf("-----\n");
}


void change_element(int* matrix, int* mask, int pos, int el) {
	if (*(mask + pos) == 1) {
		*(matrix + pos) = el;
	}
}


int check_matrix(int* matrix, int MSIZE) {
	int s = 1;
	for (int i = 0; i < MSIZE * MSIZE; i++) {
		if (*(matrix + i) == 0) {
			s = 0;
			break;
		}
	}
	return s;
}


int randint(int minint, int maxint) {
	return minint + (rand() % (maxint - minint + 1));
}


void gen_matrix(int* a, int MSIZE) {
	int s[9];
	int t;
	if (MSIZE == 4) {
		int s[4] = {1, 3, 2, 4};
	} else {
		int s[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
	}
	// int s[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
	for (int i = 0; i < MSIZE; i++) {
		for (int k = 0; k < MSIZE; k++) {
			t = (s[i] + k) % MSIZE;
			if (t == 0) {
				t = MSIZE;
			}
			*(a + i * MSIZE + k) = t;
		}
	}
}


void shake_matrix(int* matrix, int MSIZE) {
	int rand = randint(0, 20);
	int t, t1, t2, hp, sz;
	int t3, t4;
	int m[MSIZE];
	for (int i = 0; i < MSIZE; i++) {
		m[i] = 0;
	}
	if (MSIZE == 4) {
		sz = 2;
	} else {
		sz = 3;
	}
	for (int i = 0; i < rand; i++) {
		t = randint(1, 4);
		if (t == 1) {
			t1 = randint(0, MSIZE - 1);
			hp = t1 / sz;
			t2 = randint(hp * sz, hp * sz + sz - 1);
			// printf("%d - %d - %d\n", t1, hp, t2);
			for (int k = 0; k < MSIZE; k++) {
				*(m + k) = *(matrix + t1 * MSIZE + k);
			}
			for (int k = 0; k < MSIZE; k++) {
				*(matrix + t1 * MSIZE + k) = *(matrix + t2 * MSIZE + k);
			}
			for (int k = 0; k < MSIZE; k++) {
				*(matrix + t2 * MSIZE + k) = *(m + k);
			}
		} else if (t == 2) {
			t3 = randint(0, sz - 1);
			// hp = t1 / MSIZE;
			t4 = randint(0, sz - 1);
			for (int p = 0; p < sz; p++) {
				t1 = t3 * sz + p;
				t2 = t4 * sz + p;
				// printf("%d - %d\n", t1, t2);
				for (int k = 0; k < MSIZE; k++) {
					*(m + k) = *(matrix + t1 * MSIZE + k);
				}
				for (int k = 0; k < MSIZE; k++) {
					*(matrix + t1 * MSIZE + k) = *(matrix + t2 * MSIZE + k);
				}
				for (int k = 0; k < MSIZE; k++) {
					*(matrix + t2 * MSIZE + k) = *(m + k);
				}
			}
		} else if (t == 3) {
			t1 = randint(0, MSIZE - 1);
			hp = t1 / sz;
			t2 = randint(hp * sz, hp * sz + sz - 1);	
			// printf("%d - %d - %d\n", t1, hp, t2);
			for (int k = 0; k < MSIZE; k++) {
				*(m + k) = *(matrix + k * MSIZE + t1);
			}
			for (int k = 0; k < MSIZE; k++) {
				*(matrix + k * MSIZE + t1) = *(matrix + k * MSIZE + t2);
			}
			for (int k = 0; k < MSIZE; k++) {
				*(matrix + k * MSIZE + t2) = *(m + k);
			}			
		} else {
			t3 = randint(0, sz - 1);
			// hp = t1 / MSIZE;
			t4 = randint(0, sz - 1);
			for (int p = 0; p < sz; p++) {
				t1 = t3 * sz + p;
				t2 = t4 * sz + p;
				// printf("%d - %d\n", t1, t2);
				for (int k = 0; k < MSIZE; k++) {
					*(m + k) = *(matrix + k * MSIZE + t1);
				}
				for (int k = 0; k < MSIZE; k++) {
					*(matrix + k * MSIZE + t1) = *(matrix + k * MSIZE + t2);
				}
				for (int k = 0; k < MSIZE; k++) {
					*(matrix + k * MSIZE + t2) = *(m + k);
				}
			}
		}
	}
}


void edit_matrix(int* a, int* b, int MSIZE) {
	int td = 0, fl = 0, r = 0;

	for (int i = 0; i < MSIZE * MSIZE; i++) {
		*(b + i) = 0;
	}

	if (MSIZE == 4) {
		td = 9;
	} else {
		td = 56;
	}

	for (int i = 0; i < td; i++) {
		fl = 0;
		while (fl == 0) {
			r = randint(0, MSIZE * MSIZE);
			if (*(a + r) == 0) {
				continue;
			} else {
				*(a + r) = 0;
				*(b + r) = 1;
				fl = 1;
			}
		}
	}

}


int** create_matrix(int MSIZE) {
	srand(time(NULL));

	int* matrix = (int*)malloc(MSIZE * MSIZE * sizeof(int));
	int* mask = (int*)malloc(MSIZE * MSIZE * sizeof(int)); // 0 - cannot change, 1 - can

	int** rasp = (int**)malloc(2 * sizeof(int*));
	rasp[0] = matrix;
	rasp[1] = mask;

	gen_matrix(matrix, MSIZE);
	// printm(matrix);

	shake_matrix(matrix, MSIZE);

	edit_matrix(matrix, mask, MSIZE);
	// printm(matrix, mask, -1);

	return rasp;
}


int get_next_pos(int* matrix, int MSIZE) {
	int r = -1;
	for (int i = 0; i < MSIZE * MSIZE; i++) {
		if (*(matrix + i) == 0) {
			r = i;
			break;
		}
	}
	return r;
}


void clear_terminal() {
    printf("\033[H\033[J");
}


void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}


int end_game(int* matrix, int* mask, int MSIZE) {
	int s = 1, t = 0, sz = 0, c = 0;

	// rows block
	for (int i = 0; i < MSIZE; i++) {
		int a[MSIZE];
		for (int i = 0; i < MSIZE; i++) {
			a[i] = 0;
		}
		for (int k = 0; k < MSIZE; k++) {
			t = *(matrix + i * MSIZE + k);
			if (t == 0) {
				continue;
			}
			*(a + t - 1) += 1;
		}
		for (int k = 0; k < MSIZE; k++) {
			if (*(a + k) > 1) {
				s = 0;
				break;
			}
		}
		if (s == 0) {
			break;
		}
	}

	if (s == 0) {
		return 0;
	}

	// cols block
	for (int i = 0; i < MSIZE; i++) {
		int a[MSIZE];
		for (int i = 0; i < MSIZE; i++) {
			a[i] = 0;
		}
		for (int k = 0; k < MSIZE; k++) {
			t = *(matrix + k * MSIZE + i);
			if (t == 0) {
				continue;
			}
			*(a + t - 1) += 1;
		}
		for (int k = 0; k < MSIZE; k++) {
			if (*(a + k) > 1) {
				s = 0;
				break;
			}
		}
		if (s == 0) {
			break;
		}
	}

	if (s == 0) {
		return 0;
	}

	// blocks block
	if (MSIZE == 4) {
		sz = 2;
	} else {
		sz = 3;
	}

	for (int i = 0; i < sz; i++) {
		for (int k = 0; k < sz; k++) {
			int a[MSIZE];
			for (int i = 0; i < MSIZE; i++) {
				a[i] = 0;
			}
			c = i * sz * MSIZE + k * sz;
			for (int j = 0; j < sz; j++) {
				for (int p = 0; p < sz; p++) {
					t = *(matrix + c + j * MSIZE + p);
					if (t == 0) {
						continue;
					}
					// printf("\n%d\n", t);
					*(a + t - 1) += 1;
				}
			}

			for (int k = 0; k < MSIZE; k++) {
				if (*(a + k) > 1) {
					s = 0;
					break;
				}
			}
			if (s == 0) {
				break;
			}
		}
		if (s == 0) {
			break;
		}	
	}
	
	return s;
}


void check_game(int* matrix, int* mask, int MSIZE) {
	int end = end_game(matrix, mask, MSIZE);
	clear_terminal();
	printf("---(%d)---\n", end);
	if (end) {
		printf("you won!");
	} else {
		printf("you lost!");
	}
}


void edit_mode(int MSIZE) {
	// 3 25 7 22
	char ch;
    enable_raw_mode();
    //printf("123");
    int** rasp = create_matrix(MSIZE);
    int* matrix = *(rasp);
    int* mask = *(rasp + 1);
    int pos = 0, t = 0, ti = 0, flag = 0;
    clear_terminal();
    printf("для выхода нажмите 'q'\n");
    printm(matrix, mask, pos, MSIZE);
    
    while (1) {
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            if (ch == 'q') {
                break;
            }
            clear_terminal();
            t = 'z' - ch;
            ti = ch - '0';
            if (t == 3) {
            	if (pos >= MSIZE) {
            		pos -= MSIZE;
            	} else {
            		pos = MSIZE * (MSIZE - 1) + (pos % MSIZE);
            	}
            } else if (t == 25) {
            	if (pos != 0) {
            		pos--;
            	}
            } else if (t == 7) {
            	if ((pos + MSIZE) < MSIZE * MSIZE) {
            		pos += MSIZE;
            	} else {
            		pos = pos % MSIZE;
            	}
            } else if (t == 22) {
            	if (pos < MSIZE * MSIZE - 1) {
            		pos++;
            	}
            } else if (ti >= 0 && ti <= 9) {
            	if (MSIZE == 4) {
            		if (ti <= 4) {
            			change_element(matrix, mask, pos, ti);
            		}
            	} else {
            		change_element(matrix, mask, pos, ti);
            	}
            }

            printf("(%d) для выхода нажмите 'q'\n", ch - '0');
            printm(matrix, mask, pos, MSIZE);

            flag = check_matrix(matrix, MSIZE);
            if (flag == 1) {
            	// break;
            	// end_game(matrix, mask);
            	break;
            }
        }
    }
    // printf("123");
   	disable_raw_mode();
   	// printf("321");
   	check_game(matrix, mask, MSIZE);
}


int try_bf(int* matrix, int* mask, int MSIZE) {
	int end = 0, pos = 0;
	pos = get_next_pos(matrix, MSIZE);
	if (pos == -1) {
		// clear_terminal();
		printf("\nyou won!");
		exit(0);
	}
	// clear_terminal();
	for (int i = 1; i <= MSIZE; i++) {
		*(matrix + pos) = i;
		clear_terminal();
		printm(matrix, mask, -2, MSIZE);
		end = end_game(matrix, mask, MSIZE);
		// printf("\n--- ---\n");
		usleep(100000 / SPEED);
		if (end) {
			try_bf(matrix, mask, MSIZE);
		}
	}
	*(matrix + pos) = 0;
}


void bruteforce_mode(int MSIZE) {
    int** rasp = create_matrix(MSIZE);
    int* matrix = *(rasp);
    int* mask = *(rasp + 1);
    try_bf(matrix, mask, MSIZE);
}


int main() {
	msize MSIZE;

	printf("\nразмер поля (4/9): \n");
	scanf("%d", &MSIZE);

	if (MSIZE != 4 && MSIZE != 9) {
		printf("\nневерный размер поля!\n"); 
		exit(0);
	}
	// edit_mode(MSIZE);
	#ifndef BF
		edit_mode(MSIZE);
	#else
		bruteforce_mode(MSIZE);
	#endif
}

