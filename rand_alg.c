#include "rand_alg.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

RandNode rn[] = {
	{	.count		= 1,
		.rand_min	= 5,
		.delta		= 95,
	},{
		.count		= 30,
		.rand_min	= 10,
		.delta		= 8,
	},{
		.count		= 30,
		.rand_min	= 7,
		.delta		= 6,
	},{
		.count		= 30,
		.rand_min	= 6,
		.delta		= 2,
	},{
		.count		= 15,
		.rand_min	= 5,
		.delta		= 2,
	},{
		.count		= 7,
		.rand_min	= 4,
		.delta		= 2,
	},{
		.count		= 7,
		.rand_min	= 3,
		.delta		= 2,
	},{
		.count		= 7,
		.rand_min	= 1,
		.delta		= 0,
	}
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

RandAlg ra = {
	.node = rn,
	.node_sz = ARRAY_SIZE(rn),
	.min = 5,
	.max = 100,
};

void RandAlg_Init(RandAlg *ra)
{
	ra->curr = 0;
	ra->count = 0;
}

int RandAlg_GetRandInt(int low, int high)
{
	return rand() % ((high + 1) - low) + low;
}

int RangAlg_Find_Id(RandAlg *ra)
{
	int count = ra->node[0].count;
	int range_id = -1;
	for(int id = 0; id < ra->node_sz; id++) {
		///printf("->id:%i\n",id);
		count += ra->node[id].count;
		if(ra->count < count) {
			range_id = id;
			break;
		}
		///printf("count:%i\n",count);
	}
	///printf("rang_id:%i\n",range_id);
	fflush(stdout);
	return range_id;
}

int RandAlg_Step(RandAlg *ra,int *Id)
{
	int id = RangAlg_Find_Id(ra);
	///printf("----id:%i---\n",id);

	int rand_min = ra->node[id].rand_min;
	int rand_max = rand_min + ra->node[id].delta;
	int rand = RandAlg_GetRandInt(rand_min,rand_max);

	///printf("Rand:%i\n",rand);

	ra->curr += rand;

	//TODO А если на 2 круг?
	while( ra->curr > ra->max) {
	//if( ra->curr > ra->max ) {
		ra->curr = (ra->curr - ra->max) + ra->min;
		//printf("Test\n");
		fflush(stdout);
	}

	//printf("Rand:%i\n",ra->curr);

	ra->count++;

	if(Id != NULL) {
		*Id = id;
	}

	fflush(stdout);
	return ra->curr;
}

void RandAlg_TestInit()
{
	srand(time(NULL));
	RandAlg_Init(&ra);
}

void RandAlg_TestLoop()
{
	int id = 0;
	while(id >= 0) {
		int rand = RandAlg_Step(&ra,&id);
		printf("Rand:%i id:%i\n",rand,id);
	}
}

RandAlg *RandAlg_Get()
{
	return &ra;
}

void RandAlg_SetMinMax(RandAlg *ra, int min, int max)
{
	ra->min = min;
	ra->max = max;

	ra->node[0].rand_min = min;
	ra->node[0].delta = max - min;
}

