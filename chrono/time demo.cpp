#include <iostream>
#include <chrono>
// #include <ratio>
#include <iomanip> //put_time
using namespace std;

int main(int argc, const char *argv[])
{
	std::chrono::duration<int, std::ratio<1, 1>> a(30);		  //30��
	std::chrono::duration<int> b(30);						  //30��
	std::chrono::duration<int, std::ratio<1, 1000>> c(30000); //30 000����
	std::chrono::duration<double, std::ratio<60, 1>> d(0.5);  //�����

	using Minus = std::chrono::duration<int, std::ratio<60>>;
	Minus::rep min_e = 30; //min_e��int����
	Minus::period min_per; //per�������� std::ration<60, 1>����min_per.num Ϊ60�� min_per.den Ϊ1

	Minus twenty_minutes(20);
	decltype(twenty_minutes.count()) min_count = 30; //��������count()�ķ���ֵ����, min_count������Ϊint
	decltype(twenty_minutes)::rep min_rep = 40;		 //min_rep������Ϊint

	std::chrono::seconds twenty_sec(20);
	int isec = twenty_sec.count(); //isec����20

	std::chrono::duration<double> half_sec(0.5);
	std::cout << d.count() << "min = " << chrono::duration_cast<std::chrono::seconds>(d).count() << "seconds" << endl;
	std::cout << half_sec.count() << "seconds = " << chrono::duration_cast<std::chrono::milliseconds>(half_sec).count() << "milliseconds" << endl;

	auto tp_now = std::chrono::system_clock::now();
	std::time_t cur_time = std::chrono::system_clock::to_time_t(tp_now);
	char *strtime = std::ctime(&cur_time);
	std::cout << "\nnow: " << strtime;

	//requires gcc version >= 5.0
	// struct std::tm * ptm_cur_time= std::localtime(&cur_time);
	// std::cout << "put_time: " << std::put_time(ptm_cur_time, "%Y-%m-%d %X") << endl;
	// std::cout << "put_time: " << std::put_time(ptm_cur_time, "%Y-%m-%d %H-%M-%S") << endl;

	std::chrono::system_clock::time_point tp_10hours = tp_now + std::chrono::hours(10);
	std::time_t time_t_10hours = std::chrono::system_clock::to_time_t(tp_10hours);
	char *str10hourslater = std::ctime(&time_t_10hours);
	std::cout << "10 hours later: " << str10hourslater << std::endl;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::cout << "Hello World\n";
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Printing took "
			  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
			  << "us.\n";

	//time_point��һ��time_since_epoch()��Ա���������ش�epochʱ�䵽�˿̵�ʱ���
	//����system_clock��high_resolution_clock��˵��epoch��1970-01-01T00:00:00
	//steady_clockʱ������boot����ʱ�䣬���Բ�Ӧ�ö�steady_clock::now()���ص�time_point����time_since_epoch()
	auto tp_steady_clock = std::chrono::steady_clock::now();
	std::time_t cur_time_steady_clock = std::chrono::duration_cast<std::chrono::seconds>(tp_steady_clock.time_since_epoch()).count();
	std::string str_time_csteady_clock = std::ctime(&cur_time_steady_clock);
	cout <<"\ntime_since_epoch: "<< str_time_csteady_clock;

	using days_type = std::chrono::duration<int, std::ratio<60 * 60 * 24>>;
	std::chrono::time_point<std::chrono::system_clock, days_type> today = std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;


	return 0;
}
