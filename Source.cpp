#include <iostream>
#include <string>
#include <iostream>
#include <algorithm> 
#include <vector>
using namespace std;


void inti();


void inti()
{

	int p[8][21] = { { 1, 1, 4, 15, 5, 31, 6, 26, 7, 24, 6, 41, 4, 51, 5, 16, 4 },
	{ 2, 1, 9, 28, 11, 22, 15, 21, 12, 28, 8, 34, 11, 34, 9, 29, 10, 31, 7 },
	{ 3, 1, 24, 28, 12, 21, 6, 27, 17, 21, 11, 54, 22, 31, 18 },
	{ 4, 1, 15, 35, 14, 41, 16, 45, 18, 51, 14, 61, 13, 54, 16, 61, 15 },
	{ 5, 1, 6, 22, 5, 21, 15, 31, 4, 26, 7, 31, 4, 18, 6, 21, 10, 33, 3 },
	{ 6, 1, 22, 38, 27, 41, 25, 29, 11, 26, 19, 32, 18, 22, 6, 26, 6 },
	{ 7, 1, 4, 36, 7, 31, 6, 32, 5, 41, 4, 42, 7, 39, 6, 33, 5, 34, 6, 21, 9 },
	{ 8, 1, 5, 14, 4, 33, 6, 31, 4, 31, 6, 27, 5, 21, 4, 19, 6, 11, 6 } };

	int cb = 0; // current burst
	int ct = 0; // current time
	int end = 1; // int to end loop
	int et[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //end time
	int st[8] = { 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 }; //respose time array
	int tb[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //total burts time array
	int cp = 0; //current proccess



	//current burst or io withen the array;


	//array of currect burst or IO times
	int cs[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };

	vector<int> ready = { 1, 2, 3, 4, 5, 6, 7, 8 }; // main ready queue vector
	//vectors for each queue level
	vector<int> ready1 = { 1, 2, 3, 4, 5, 6, 7, 8 };
	vector<int> ready2;
	vector<int> ready3;
	//IO queue vector
	vector<int> io;
	// for switching between IO and ready
	vector<int> temp;

	//main loop
	while (end != 0)
	{
		end = 0;
		int procom = 0; // tells if the proccess burst is less than or equal to the tq and does not get interupted
		int procom2 = 0; // tells if the proccess burst is less than or equal to the tq
		int ql = 0; //current proccess queue level

		//to indicate whether a queue lv should be moved, think of the i's as roman numerals
		int itoii = 0;
		int iitoii = 0;
		int iitoiii = 0;
		int iiitoiii = 0;

		//test whether all processes are done
		for (int i = 0; i < 8; i++)
		{
			if (cs[i]>0)
			{
				end = 1;
			}
		}

		//update current burst of porcess and which vector to place them in next
		if (!ready.empty())
		{
			for (int i = 0; i < 8; i++)
			{
				if (ready[0] == p[i][0])
				{ 
					cp = i;
					//sorting q1
					if (p[i][1] == 1)
					{
						ql = 1;
						if ((p[i][cs[i]]) <= 6)
						{
							cb = p[i][cs[i]];
							cs[i] = cs[i] + 1;
							procom = 1;
						}
						else
						{
							cb = 6;
							p[i][cs[i]] = p[i][cs[i]] - 6;
							p[i][1] = p[i][1] + 1;
							procom = 0;
							itoii = 1;
						}

						if (!ready1.empty())
						{
							//update ready queue
							ready1.erase(ready1.begin());
						}

						cout << "Current time:\t" << ct << endl << endl;
						cout << "Now running:\t" << "p" << ready[0] << "\t" << "time: " << cb<< endl;
					}

					//sorting q2
					else if (p[i][1] == 2)
					{
						ql = 2;
						if (p[i][cs[i]] <= 12)
						{
							cb = p[i][cs[i]];
							procom = 1;
							procom2 = 1;
						}
						else
						{
							cb = 12;
							procom = 0;
						}

						if (!io.empty())
						{
							for (int i = 0; i < io.size(); i++)
							{
								
								if (p[io[i] - 1][1] == 1 && cb > p[io[i] - 1][cs[io[i] - 1]])
								{
									cb = p[io[i] - 1][cs[io[i] - 1]];
									procom = 0;
									procom2 = 1;
								}
							}
						}

						if (procom == 0)
						{
							p[ready[0] - 1][cs[i]] = p[ready[0] - 1][cs[i]] - cb;
							if (procom2 == 1)
							{
								iitoii = 1;
							}
							else
							{
								p[i][1] = p[i][1] + 1;
								iitoiii = 1;
							}

						}
						else
						{
							cs[i] = cs[i] + 1;
						}
						//update ready2 queue
						if (!ready2.empty())
						{
							ready2.erase(ready2.begin());
						}
						cout << "Current time:\t" << ct << endl << endl;
						cout << "Now running:\t" << "p" << ready[0] << "\t" << "time: " << cb << "\t" << "QL: " << p[i][1] << endl;
					}

					//sorting q3
					else if (p[i][1] == 3)
					{
						ql = 3;
						cb = p[i][cs[i]];
						procom = 1;

						if (!io.empty())
						{
							for (int i = 0; i < io.size(); i++)
							{

								if (p[io[i] - 1][1] == 2 && cb > p[io[i] - 1][cs[io[i] - 1]])
								{
									cb = p[io[i] - 1][cs[io[i] - 1]];
									procom = 0;
								}

								if (p[io[i] - 1][1] == 1 && cb > p[io[i] - 1][cs[io[i] - 1]])
								{
									cb = p[io[i] - 1][cs[io[i] - 1]];
									procom = 0;
								}
							}
						}

						if (procom == 0)
						{
							p[ready[0] - 1][cs[i]] = p[ready[0] - 1][cs[i]] - cb;
							iiitoiii = 1;

						}
						else
						{
							cs[i] = cs[i] + 1;
						}

						cout << "Current time:\t" << ct << endl << endl;
						cout << "Now running:\t" << "p" << ready[0] << "\t" << "time: " << cb << "\t" << "QL: " << p[i][1] << endl;
						//update ready queue
						if (!ready3.empty())
						{
							ready3.erase(ready3.begin());
						}
						

					}

					//if a proccess is completed
					if (cs[i] >= 21 || p[i][cs[i]] == 0)
					{
						cs[i] = 0;
						cout << "Proccess complete p" << i + 1 << "!" << endl << endl;
						et[i] = cb + ct;
						procom = 0;
					}
					tb[i] = tb[i] + cb;
					cout << "--------------------------------------------------------------------------------" << endl;
				}
			}
			//update ready queue
			//rotate(ready.begin(), ready.begin() + 1, ready.end());
			//ready.pop_back();
			ready.erase(ready.begin());
		}
		else // if ready vector is empty
		{
			cout << "Current time:\t" << ct << endl << endl;
			if (io.size() > 1)
			{
				int less = 0;
				for (int i = 1; i < io.size(); i++)
				{
					if (p[io[less] - 1][cs[io[less] - 1]] > p[io[i] - 1][cs[io[i] - 1]])
					{
						less = i;
					}
				}
				cb = p[io[less] - 1][cs[io[less] - 1]];
				cp = 0;
			}
			else if (io.size() == 0)
			{
			}
			else
			{
				cb = p[io[0] - 1][cs[io[0] - 1]];
				cp = 0;
			}
		}



		//print ready queue
		cout << "Process queue:" << endl;
		if (!ready.empty())
		{
			for (int i = 0; i < ready.size(); i++)
			{

				cout << "Process: p" << ready[i] << "\t" << "Burst: " << p[ready[i] - 1][cs[ready[i] - 1]] <<  "\t";
				cout << "QL: " << p[ready[i] - 1][1] << endl;
			}
		}
		else
		{
			cout << "[empty]" << endl;
		}

		/*
		//update ready queue
		if (procom = 0)
		{
			for (int i = 0; i < ready.size(); i++)
			{
				if (p[cp][1] <= )
				{

				}
			}
		} */

		//print io queue
		cout << "--------------------------------------------------------------------------------" << endl << "IO queue" << endl;
		if (!io.empty())
		{
			for (int i = 0; i < io.size(); i++)
			{
				cout << "Process: p" << io[i] << "\t" << "IO: " << p[io[i] - 1][cs[io[i] - 1]] << "\t";
				cout << "QL: " << p[io[i] - 1][1] << endl;
			}


			//update io queue
			int i = 0;
			do
			{
				if (p[io[i] - 1][cs[io[i] - 1]] <= cb)
				{
					temp.push_back(io[i]);
					//erase.push_back(i);
					io.erase(io.begin() + i);
				}
				else
				{
					p[io[i] - 1][cs[io[i] - 1]] = p[io[i] - 1][cs[io[i] - 1]] - cb;
					i++;
				}
			} while (i < io.size());


			//updating from io to ready again
			if (temp.size() > 1)
			{
				while (temp.size() > 1)
				{
					//finding least value in vector
					int least = 0;
					int l = 0;
					for (int i = 1; i < temp.size(); i++)
					{
						if (p[temp[least] - 1][cs[temp[least] - 1]] > p[temp[i] - 1][cs[temp[i] - 1]])
						{
							least = i;
						}
					}
					l = *(temp.begin() + least);

					if (p[l - 1][1] == 1)
					{
						ready1.push_back(l);
					}
					else if (p[l - 1][1] == 2)
					{
						ready2.push_back(l);
					}
					else if (p[l - 1][1] == 3)
					{
						ready3.push_back(l);
					}
					cs[temp[least] - 1]++; //updating the butst/ io position 
					temp.erase(temp.begin() + least); // erasing it from temp;
				}

				if (p[temp[0] - 1][1] == 1)
				{
					ready1.push_back(temp[0]);
				}
				else if (p[temp[0] - 1][1] == 2)
				{
					ready2.push_back(temp[0]);
				}
				else if (p[temp[0] - 1][1] == 3)
				{
					ready3.push_back(temp[0]);
				}

				cs[temp[0] - 1] = cs[temp[0] - 1] + 1;
				temp.pop_back();

			}

			else if (temp.size() == 1)
			{
				if (p[temp[0] - 1][1] == 1)
				{
					ready1.push_back(temp[0]);
				}
				else if (p[temp[0] - 1][1] == 2)
				{
					ready2.push_back(temp[0]);
				}
				else if (p[temp[0] - 1][1] == 3)
				{
					ready3.push_back(temp[0]);
				}
				cs[temp[0] - 1] = cs[temp[0] - 1] + 1;
				temp.pop_back();
			}
		}
		else
		{
			cout << "[empty]" << endl;
		}

		//update ready 1,2,3

		if (itoii == 1 || iitoii == 1)
		{
			ready2.push_back(cp + 1);
		}
		if (iitoiii == 1 || iiitoiii == 1)
		{
			ready3.push_back(cp + 1);
		}


		cout << "--------------------------------------------------------------------------------" << endl;

		cout << endl << "completed:" << "\t";

		for (int i = 0; i < 8; i++)
		{
			if (cs[i] == 0)
			{
				cout << "p" << i + 1 << "\t";
			}
		}
		cout << endl << "________________________________________________________________________________" << endl << endl;


		//update main ready
		ready.clear();

		if (!ready1.empty())
		{
			for (int i = 0; i < ready1.size(); i++)
			{
				ready.push_back(ready1[i]);
			}
		}
		if (!ready2.empty())
		{
			for (int i = 0; i < ready2.size(); i++)
			{
				ready.push_back(ready2[i]);
			}
		}
		if (!ready3.empty())
		{
			for (int i = 0; i < ready3.size(); i++)
			{
				ready.push_back(ready3[i]);
			}
		}

		if (st[cp] > 9000)
		{
			st[cp] = ct;
		}

		//update IO queue
		//cout << "\n\n\n" << 
		if (procom == 1)
		{
			io.push_back(cp + 1);
		}
		//updates current time
		ct = ct + cb;
	}

	ct = ct - cb;
	cout << "All processes Completed" << endl << endl << endl << endl;


	int tt[8] = { (et[0] - st[0]), (et[1] - st[1]), (et[2] - st[2]), (et[3] - st[3]), (et[4] - st[4]), (et[5] - st[5]), (et[6] - st[6]), (et[7] - st[7]) };

	int wt[8] = { (tt[0] - tb[0]), (tt[1] - tb[1]), (tt[2] - tb[2]), (tt[3] - tb[3]), (tt[4] - tb[4]), (tt[5] - tb[5]), (tt[6] - tb[6]), (tt[7] - tb[7]) };

	//updating values and averages
	double att = 0;
	double awt = 0;
	double art = 0;
	double abt = 0;
	double cpu = 0;
	for (int i = 0; i < 8; i++)
	{
		att = att + tt[i];
		awt = awt + wt[i];
		art = art + st[i];
		abt = abt + tb[i];
	}

	att = att / 8;
	awt = awt / 8;
	art = art / 8;

	cpu = (abt / ct) * 100;


	cout << "Total Time:" << "\t" << ct << endl << endl;
	cout << "CPU Utilization" << "\t" << cpu << "%" << endl << endl;

	cout << "Response Time: " << " P1: " << st[0] << ", P2: " << st[1] << ", P3: " << st[2] << ", P4: " << st[3] << ", P5: " << st[4] << ", P6: " << st[5] << ", P7: " << st[6] << ", P8: " << st[7] << endl << endl;

	cout << "Average Response Time: " << art << endl << endl;

	cout << "Turnaround Time: " << " P1: " << tt[0] << ", P2: " << tt[1] << ", P3: " << tt[2] << ", P4: " << tt[3] << ", P5: " << tt[4] << ", P6: " << tt[5] << ", P7: " << tt[6] << ", P8: " << tt[7] << endl << endl;
	cout << "Average Turnaround Time: " << att << endl << endl;

	cout << "wait Time: " << " P1: " << wt[0] << ", P2: " << wt[1] << ", P3: " << wt[2] << ", P4: " << wt[3] << ", P5: " << wt[4] << ", P6: " << wt[5] << ", P7: " << wt[6] << ", P8: " << wt[7] << endl << endl;
	cout << "Average Wait Time: " << awt << endl << endl;
}


int main()
{
	inti();

	return 0;
}