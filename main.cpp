#include "stdafx.h"
#include <cmath>
#define N 100
using namespace std;
double messege_time(double ml)
{
	double u, t;
	u = (double)(rand()) / RAND_MAX;
	t = (double)(-log(u) / ml);
	return t;
}

int main()
{
	FILE* results;
	double LastTime = 0;//вермя окончания отправки последнего сообшения
	double NewTime = 0;//время прихода нового сообщения
	double DS = 0;
	double DA = 0;
	double ADS = 0;
	double ADA = 0;
	int windows_count = 0;
	double Requests;
	double RequestsT;
	double ADST;
	double ADAT;
	results = fopen("results.csv", "w");
	fprintf(results, "lambda;deleySync;deleySyncTeory;deleyASync;deleyAsyncTeory;N(l);N() Teory\n");
	for (double ml = 0.0001; ml <= 1.0001; ml += 0.1)
	{

		LastTime = 0;
		NewTime = 0;
		for (int i = 0; i < N; i++)
		{
			NewTime = LastTime + messege_time(ml);

			if (i == N - 1)
			{
				windows_count = ceil(NewTime);
			}
			if (NewTime > LastTime + DS)
			{
				DA = 1;//сразу передаем сообщение
				DS = 1 + ceil(NewTime) - NewTime; // время до следующего окна плюс время на передачу
			}
			else
			{
				DA = 1 + DA - (NewTime - LastTime);	//время оставшееся до окончание передачи предыдущего сообщения
				DS = 1 + DS - (NewTime - LastTime);	//время оставшееся до окончание передачи предыдущего сообщения
			}
			LastTime = NewTime;


			ADA += DA;
			ADS += DS;
		}
		ADS /= N;
		ADA /= N;

		RequestsT = ((ml) * (2 - (ml))) / (2 * (1 - (ml)));
		ADAT = (double)RequestsT / ml;
		ADST = ADAT + 0.5;
		Requests = (double)N / windows_count;
		fprintf(results, " %4.6f; %4.6f; %4.6f; %4.6f; %4.6f; %4.6f; %4.6f\n", ml, ADS, ADST, ADA, ADAT, Requests, RequestsT);

	}


	return 0;
}

