#ifndef RAND_ALG_H
#define RAND_ALG_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef  struct {
	int count;
	int delta;
	int rand_min;
} RandNode;

typedef struct {
	RandNode *node;
	int node_sz;
	int min;
	int max;
	int curr;
	int count;
} RandAlg;

void RandAlg_Init(RandAlg *ra);
int RandAlg_Step(RandAlg *ra, int *Id);

void RandAlg_SetMinMax(RandAlg *ra,int min,int max);

void RandAlg_TestInit();
void RandAlg_TestLoop();
RandAlg* RandAlg_Get();

#ifdef __cplusplus
}
#endif

#endif
