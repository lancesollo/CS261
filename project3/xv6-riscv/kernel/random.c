//Random number generator

#define KK 100
#define LL 37
#define MM (1L << 30)
#define TT 70

// Inline function for modulus difference
static inline long mod_diff(long x, long y) {
    return ((x) - (y)) & (MM - 1);
}

// Check if a number is odd
static inline int is_odd(long x) {
    return x & 1;
}

// Evenize the number (clear least significant bit)
static inline long evenize(long x) {
    return x & (MM - 2);
}

long ran_x[KK];
long aa[2000];
int rand_index = 0;

// Function to populate the random array aa[]
void ran_array(long aa[], int n) {
    int j;
    // Copy the values from ran_x to aa initially
    for (j = 0; j < KK; j++) {
        aa[j] = ran_x[j];
    }
    // Generate values using the mod_diff function
    for (; j < n; j++) {
        aa[j] = mod_diff(aa[j - KK], aa[j - LL]);
    }

    // Update ran_x values
    int i;
    for (i = 0; i < LL; i++, j++) {
        ran_x[i] = mod_diff(aa[j - KK], aa[j - LL]);
    }

    for (; i < KK; i++, j++) {
        ran_x[i] = mod_diff(aa[j - KK], ran_x[i - LL]);
    }
}

// Initialize random number generator with a seed
void ran_start(int seed) {
    long x[KK + KK - 1];
    long ss = evenize(seed + 2);

    // Initialize the first part of the x array
    for (int j = 0; j < KK; j++) {
        x[j] = ss;
        ss <<= 1;
        if (ss >= MM) ss -= MM - 2;
    }

    // Set the second part of the x array to 0
    for (int j = KK; j < KK + KK - 1; j++) {
        x[j] = 0;
    }

    // Increment x[1] and process the seed
    x[1]++;
    ss = seed & (MM - 1);
    int t = TT - 1;

    while (t) {
        // Shift and modify the x array
        for (int j = KK - 1; j > 0; j--) {
            x[j + j] = x[j];
        }

        for (int j = KK + KK - 2; j > KK - LL; j -= 2) {
            x[KK + KK - 1 - j] = evenize(x[j]);
        }

        // Adjust x values based on odd/even checks
        for (int j = KK + KK - 2; j >= KK; j--) {
            if (is_odd(x[j])) {
                x[j - (KK - LL)] = mod_diff(x[j - (KK - LL)], x[j]);
                x[j - KK] = mod_diff(x[j - KK], x[j]);
            }
        }

        // If ss is odd, shift the values in x
        if (is_odd(ss)) {
            for (int j = KK; j > 0; j--) {
                x[j] = x[j - 1];
            }
            x[0] = x[KK];
            if (is_odd(x[KK])) {
                x[LL] = mod_diff(x[LL], x[KK]);
            }
        }

        // Shift ss right if it's non-zero
        if (ss) {
            ss >>= 1;
        } else {
            t--;
        }
    }

    // Update ran_x with final x values
    int j;
    for (j = 0; j < LL; j++) {
        ran_x[j + KK - LL] = x[j];
    }
    for (; j < KK; j++) {
        ran_x[j - LL] = x[j];
    }

    // Initialize aa[] and reset rand_index
    ran_array(aa, 1009);
    rand_index = 0;
}

// Generate the next random number
int nextRand() {
    if (++rand_index > 100) {
        ran_array(aa, 1009);
        rand_index = 0;
    }
    return aa[rand_index];
}

// Initialize the random number generator
void rand_init(int seed) {
    ran_start(seed);
}

// Return a scaled random value in the range [low, high]
int scaled_random(int low, int high) {
    int range = (high - low + 1);
    int val = nextRand();
    return (val % range) + low;
}
