/* DNA sequence mapper:
 *
 * Skeleton code written by Jianzhong Qi, April 2022
 * Edited by: Hogi Kwak, 1235667
 *
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define STAGE_NUM_ONE 1						  /* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n" /* stage header format string */

#define MAX_READ_ID_LENGTH 100				  /* maximum read ID length */
#define MAX_READ_LENGTH 100					  /* maximum read length */
#define MAX_NUM_READS 100					  /* maximum number of reads */
#define MAX_REF_LENGTH 1000					  /* maximum reference DNA length */
#define MIN_BOUND 33
#define BENCH_MARK 0.15
#define STAR_CASE 0.25
#define BASE_TWO 2
#define NUMERATOR 1
#define DENOMINATOR 10.0
#define DENOMINATOR_OF_POWER 10.0
#define MINUS -1

typedef char read_id_t[MAX_READ_ID_LENGTH+1]; /* a read ID */
typedef char read_t[MAX_READ_LENGTH+1];		  /* a read */
typedef char score_t[MAX_READ_LENGTH+1];	  /* quality scores of a read */
typedef char ref_t[MAX_REF_LENGTH+1];		  /* a reference DNA sequence */

/****************************************************************/

/* function prototypes */
void take_one_read(read_id_t id, read_t one_read, score_t scores_of_one_read);
void print_stage_header(int stage_num);

void stage_one(read_t one_read, score_t scores_of_one_read);
void stage_two(read_t reads[], score_t scores[], int *num_reads);
void stage_three(read_t reads[], score_t scores[], int num_reads);
void stage_four(ref_t ref_sequence);
void stage_five(read_t reads[], score_t scores[], int num_reads, 
	ref_t ref_sequence);

/* add your own function prototypes here */
/****************************************************************/



/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input reads and quality scores */
	read_t reads[MAX_NUM_READS];	
	score_t scores[MAX_NUM_READS];
	/* to hold the number of input reads */
	int num_reads = 0;	
	/* to hold the input reference sequence */
	ref_t ref_sequence;
	
	/* stage 1: process one read */
	stage_one(reads[0], scores[0]); 
	num_reads++;
	
	/* stage 2: process all reads */
	stage_two(reads, scores, &num_reads);
	
	/* stage 3: mask bases with high error probability */ 
	stage_three(reads, scores, num_reads);
	
	/* stage 4: process reference sequence */
	stage_four(ref_sequence);
	
	/* stage 5: map reads to the reference sequence */
	stage_five(reads, scores, num_reads, ref_sequence);
	
	/* all done; take some rest */
	return 0;
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

//Gain the index of max value

int max_value_index (double arr[], int n) {
    int index = 0;
    int max = arr[index];
    for (int i = n - 1; 0 <= i; i--) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
            }
        }
    return index;
}

/* process a read record */
//scan the sentence including id
void 
take_one_read(read_id_t id, read_t one_read, score_t scores_of_one_read) {
	/* modify this function for stage 2 */
	scanf("%s", id);
    if (strcmp(id, "#####") == 0) {
        return;
    }
        //printf("id %s\n",id);//
	scanf("%s", one_read);
        //printf("one %s\n",one_read);//
	getchar();
	getchar(); // skip '+' and '\n'
	scanf("%s", scores_of_one_read);
        //printf("score %s\n",scores_of_one_read);//
}

/* stage 1: process one read */
void 
stage_one(read_t one_read, score_t scores_of_one_read) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* add code for stage 1 */
	/* process first read */
    //Read the input and check the each char of scores if it is smaller than 
    //other char and you can get the smallest ascii char and this index 
    //in the end.
    //algorithms are fun
    
    read_id_t id;
    take_one_read(id, one_read, scores_of_one_read);
    int score = 0;
    int indx_of_smallest = 0;
    int i;
    for (i = 0; scores_of_one_read[i] != '\0'; i++){
        if (score==0 || score >= scores_of_one_read[i]){
            indx_of_smallest = i;
            score = scores_of_one_read[i];
        }
    }
    
    /*print the results*/
    printf("Base with the smallest quality score: %c\n", 
        one_read[indx_of_smallest]);
	printf("Index: %d\n\n", indx_of_smallest);
    }


/* stage 2: process all reads */
void 
stage_two(read_t reads[], score_t scores[], int *num_reads) {

    /* print stage header */
    print_stage_header(STAGE_NUM_TWO);
    
    /* add code for stage 2 */
    //Get set(id, reads, + and scores) and stop when # appears,
    //otherwise keep the loop and get the total of ascii for each score line
    //and find average of them.
    //NEED to initialise 1 because it already got 
    //first set(id, reads, + and scores).
    
    read_id_t id;
    int index_of_base = 0;
    double the_smallest_aver = 0; 
    
    int i = 1;
    while(strcmp(id, "#####")){
        take_one_read(id, reads[i], scores[i]); 
        if (id[0] == '#'){
            break;
        }
        *num_reads += 1;
        int dnmtr = 0;
        double sum = 0;
        for (dnmtr=0; scores[i][dnmtr] != '\0'; dnmtr++){
            sum += scores[i][dnmtr];
        }
        double aver = sum / dnmtr;
        if(the_smallest_aver == 0 || aver < the_smallest_aver){
            index_of_base = i;
            the_smallest_aver = aver;
        }
        i++;  
    }
    printf("Total number of reads: %d\n", *num_reads);
    printf("Smallest average quality score: %.2lf\n", the_smallest_aver);
    printf("Read with the smallest average quality score:\n");
    printf("%s\n\n",  reads[index_of_base]);
}

/* stage 3: mask bases with high error probability */ 
void 
stage_three(read_t reads[], score_t scores[], int num_reads) {
	/* add code for stage 3 */
    print_stage_header(STAGE_NUM_THREE);
    
    //In the loop of reads, you need loop for the each char of score line then
    //you need to get probability(if bigger than 0.15, it returns *. If not,
    //it does not change the char.
    
    //printf("ini %s\n", reads[0]);
    //printf("ini %s\n", scores[0]);
    //printf("ini %c\n", reads[0][0]);
    int i = 0;
    while (i < num_reads) {
        int j=0;
        while (scores[i][j] != '\0') {
            //printf("aa %c\n", reads[i][j]);
            double p;
            double power = (scores[i][j] - MIN_BOUND) / DENOMINATOR_OF_POWER;
            p = NUMERATOR / pow(DENOMINATOR, power);
            if (p > BENCH_MARK) {
                reads[i][j] = '*';
            } 
            j++;
        }
        printf("%s\n", reads[i]);
        i++;
    }
    printf("\n");
}

/* stage 4: process reference sequence */
void stage_four(ref_t ref_sequence) {
	/* add code for stage 4 */
    print_stage_header(STAGE_NUM_FOUR);
    
    //It loops to get the total number of char of reference 
    //and stop NULL appears. And in this loop, calculate the total number 
    //of each charactor in reference and return them.
    
    scanf("%s", ref_sequence);
    int A_count=0, C_count=0, G_count=0, T_count=0;
    int count = 0;
    while (ref_sequence[count] != '\0'){
        if(ref_sequence[count] == 'A'){
            A_count++;
        }
        else if (ref_sequence[count] == 'C'){
            C_count++;
        }
        else if (ref_sequence[count] == 'G'){
            G_count++;
        }
        else if (ref_sequence[count] == 'T'){
            T_count++;
        }
        count++;
    }
    printf("Length of the reference sequence: %u\n", strlen(ref_sequence));
    printf("Number of A bases: %d\n", A_count);
    printf("Number of C bases: %d\n", C_count);
    printf("Number of G bases: %d\n", G_count);
    printf("Number of T bases: %d\n", T_count);
    printf("\n");
}

/* stage 5: map reads to the reference sequence */
void 
stage_five(read_t reads[], score_t scores[], int num_reads, 
ref_t ref_sequence) {
	/* add code for stage 5  */
    print_stage_header(STAGE_NUM_FIVE);
    
    //Read the all of char for each reference and then char for each 
    //reads using loop. 
    //In tsi loop, you need to get probability and then, calculate with exact 
    //same probability if char of reads and char of ref is same, calculate 
    //with 0.25 if char of reads is *, otherwise return 1, then match_score
    //will be multiplied by -1.
    //Then, you need to output the Read and Match using loop.
    
    int limiter = 1;
    int len_reads_arr[num_reads];
    int ans_index;
    double match_score_arr[num_reads][MAX_REF_LENGTH];
    
    int i = 0;
    while (ref_sequence[i] != '\0') {
        int j = 0;
        while (j < num_reads) {
            int ref_i = i;
            double match_score = 0;
            int k=0;
            while (reads[j][k] != '\0') {
                double power = (scores[j][k] - MIN_BOUND) 
                    / DENOMINATOR_OF_POWER;
                double prob = NUMERATOR / pow(DENOMINATOR, (power));
                if (reads[j][k] == ref_sequence[ref_i]) {
                    match_score += (log(prob) / log(BASE_TWO));
                }
                else if (prob > BENCH_MARK) {
                    reads[j][k] = '*';
                    match_score += (log(STAR_CASE) / log(BASE_TWO));
                } 
                ref_i++;
                k++;
            }
            if (limiter == 1) {
                len_reads_arr[j] = k;
            }
            match_score = match_score * (MINUS);
            match_score_arr[j][i] = match_score;
            j++;
        }
        //Need to initialise to 0
        limiter = 0;
        i++;
        
    }
    
    int x = 0;
    while (x < num_reads) {
        ans_index = max_value_index(match_score_arr[x], i);
        printf("Read:  %s\n", reads[x]);
        //printf("Final Index: %d\n", ans_index);
        printf("Match: ");
        int y = ans_index;
        while (y < (len_reads_arr[x] + ans_index)) {
            printf("%c", ref_sequence[y]);
            y++;
        }
        printf("\n");
        x++;
       
    }
}
               
               