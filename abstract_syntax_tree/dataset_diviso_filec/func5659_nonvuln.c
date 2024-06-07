void make_random_permutation(int start) {
        int i, j;

        permutation[0] = start;	
        for (i = 1; i < ARRAY_SIZE; i++) {
                j = random() * (double)(i + 1) / RAND_MAX; 
                if (j != i) { 
                  permutation[i] = permutation[j];
                }
                permutation[j] = start + i;
        }
}