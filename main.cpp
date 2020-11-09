#include <iostream>
#include <ctime>
#include<io.h>
#include<vector>
#include<string>
#include<Windows.h>
#include<fstream>
#include<dir.h>
//#include<shellapi.h>
using namespace std;

template<class T>
void random_sort(T *s,int max){
	for (int i = 0; i < max;i++){
		int t=rand()%max;
		int tmp = *(s + i);
		*(s + i) = *(s + t);
		*(s + t) = tmp;
	}
}



void getFiles( string path, vector<string>& files ){
	//文件句柄
	long   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}

}

int Num_Count(FILE* p){
	int count=0;
	char c=' ';
	while(!feof(p)){
		fscanf(p,"%c",&c);
		if (c == ':')
			count++;
		}
	fclose(p);
	return (count/2);
}

int Check_txt(const char *s){
	int i = 0, j = 3;
	if(s[0]=='\0')
		return -1;
	if(s[1]=='\0')
		return -1;
	if(s[2]=='\0')
		return -1;
	if(s[3]=='\0')
		return -1;
	while(s[j]!='\0'){
		j++;
		i++;
	}
	if((s[i]=='t')&&(s[i+1]=='x')&&(s[i+2]=='t'))
		return 1;
	return 0;
}

int main(){
	SetConsoleOutputCP(65001);
	srand(time(NULL));
	int *a;
	FILE *fp;
	int MAX;
	char target[10000];
	char index[10000];
	vector<string> files;
	getcwd(index, 10000);
	getFiles(index,files);
	int size = 0,point=0;
	int t[1000];
	for(int i=0;i<files.size();i++){
		if(Check_txt(files[i].c_str()) == 1){
			size++;
			t[point++] = i;
		}
	}
	if(size==1)
		strcpy(target , files[t[0]].c_str());
	else if(size==0){
		cout << "未检测到目录下有txt文件存在，输入回车以退出";
		getchar();
		return 0;
	}
	else{
		cout << "检测到目录下有多个文件，请输入序号选择\n";
		for (int i = 0; i < size;i++){
			cout <<i<< ">>>" << files[t[i]].c_str() << endl;
		}
		cout << "请输入：\n";
		int i;
		cin >> i;
		strcpy(target , files[t[i]].c_str());
	}
	fp=fopen(target,"r+");
	MAX=Num_Count(fp);
	fp = fopen(target, "r+");
	a = new int[MAX];
	for (int i = 0; i < MAX;i++){
		*(a + i) = i;
	}
	for (int i = 0; i < MAX;i++)
		random_sort(a, MAX);
	


	ofstream fout("main.html");
    streambuf *coutbackup;
    coutbackup = cout.rdbuf(fout.rdbuf());

	cout << "<html>" << endl;
	cout << "<body>" << endl;
	cout << "<h1>" << endl;
	cout << "<pre>" << endl;
	cout << "<center>" << endl;
	for (int i = 0; i < MAX;i++){
		char buf = ' ';
		char s[10000];
		int point = 0;
		while(buf!=':'){
			fscanf(fp, "%c", &buf);
		}
		buf = ' ';
		while(buf!=':'){
			fscanf(fp, "%c", &buf);
			if(buf!=':'&&buf!='\n') 
				cout << buf;
		}
		cout << s << "\t";
		cout << "  "  ;
		cout << a[i] +1<<endl;
	}
	cout << "</center>" << endl;
	cout << "</pre>" << endl;
	cout << "</h1>" << endl;
	cout << "<hr/>" << endl;
	cout << "<p>建议将此文件(main.html)复制到保存的位置，下一次运行该程序时将刷新上次结果<br/>Made by Colin</p>" << endl;
	cout<<"<a href='https://github.com/cocolinfff/Random_Sort'>来自Github::Random_Sort</a><br>"<<endl;
	cout << "</body>" << endl;
	cout << "</html>" << endl;
	
	
	
//	ShellExecute(Handle, "open", "http:// ;www.neu.edu.cn", "", "", SW_SHOWNORMAL); 
	ShellExecute(NULL, TEXT("open"), TEXT("main.html"), NULL, NULL, SW_SHOWNORMAL);	
//	getchar();

	cout.rdbuf(coutbackup);
    fout.close();
	delete[] a;
	
}  