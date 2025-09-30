#ifndef da_stuff
#define da_stuff


#include <assert.h>

#define WARNING(...)        fprintf(stdout, __VA_ARGS__)
#define ERROR_BREAK(...)    fprintf(stderr, __VA_ARGS__); exit(-1)
#define LOG(...)     			  fprintf(stdout, __VA_ARGS__)
#define PAUSE()           {char a; fputs(a, stdin);}
#define CLAMP(X, LOW, HIGH) {if((X) < (LOW)) (X) = (LOW); if((X) > (HIGH)) (X) = (HIGH);}
#define ASSERT(msg) {fprintf(stderr, "aseert in:\n\tFILE %s\n\tLINE %d\n\tmsg: %s" , __FILE__, __LINE__, msg); exit(-1);}
#define DROP(var) {(void)var;}


#define ERR_JSON(json) if(json == NULL) {ASSERT("ERR in "#json"");}
#define MESSAGE(msgPTR) da_append(&engine->messeges, (msgPTR))
#define MESSAGE_F(...) {char *msg = malloc(128);  snprintf(msg, 128, __VA_ARGS__);  da_append(&engine->messeges, (msg));}


#define DA_SIZE 16
#define da_append(da, item)                                                            \
	do {                                                                                 \
		if ((da)->count >= (da)->capacity) {                                               \
			(da)->capacity = (da)->capacity == 0 ? DA_SIZE : (da)->capacity*2;               \
			(da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items));         \
			assert((da)->items != NULL && "Realloc fail !!!");                               \
			}                                                                                \
		\
		(da)->items[(da)->count++] = (item);                                               \
		} while (0)


#define da_remove_unordered(da, i)               					   \
	do {                                             					   \
		int j = (i);                              					   \
		if(j > (da)->count){ASSERT("Not that amount of elements in da");}  \
		(da)->items[j] = (da)->items[--(da)->count]; 					   \
		} while(0)

#define da_remove_last(da) do{ if((da)->count > 0){ (da)->count--; } }while(0)




#define rand_f32() ((float)rand()/(float)RAND_MAX)

#define CHANCE_NOSEE     0.33f
#define CHANCE_BIGPLANT  0.1f
#define CHANCE_STOP_RUN  0.25f 

#define MAX_SIZE_OF_JSON 20000



#endif


