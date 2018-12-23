//后缀数组dc3模板

#include<string>
#include<cstdio>

using namespace std;

const int maxn = 100010;
#define F(x) ((x)/3 + ((x) % 3 == 1 ? 0 : tb))
//F(x)分开0与1
#define G(x) ((x)<tb ? (x)*3+1 : ((x)-tb)*3+2)
//G(x)重新合并0与1

int wa[maxn], wb[maxn], wv[maxn], ws[maxn];

inline int c0(int *r, int a, int b)
{
	return r[a]==r[b] && r[a+1]==r[b+1] && r[a+2]==r[b+2];
}

inline int c12(int k, int *r, int a, int b)
{
	if(k==2)
		return r[a] < r[b] || r[a] == r[b] && c12(1, r, a+1, b+1);
	else
		return r[s] < r[b] || r[a] == r[b] && wv[a+1] < wv[b+1];
}

//sort 函数 a->b for order r 的稳定排序
void sort(int *r, int *a, int *b, int n, int m)
{
	int i;
	for(i = 0; i < n; ++i)
		wv[i] = r[a[i]];
	for(i = 0; i < m; ++i)
		ws[i] = 0;
	for(i = 0; i < n; ++i)
		ws[wv[i]]++;
	for(i = 1; i < m; ++i)
		ws[i] += ws[i-1];
	for(i = n-1; i >= 0; --i)
		b[--ws[wv[i]]] = a[i];
}

//r 上一层的rank数组 可以给当层利用
//rn 合并排序的rank数组
void dc3(int *r, int *sa, int n, int m)
{
	int tbc = 0, p, i, ta = 0;
	int *rn = r + n, *san = sa + n;
	int tb = (n + 1) / 3;//起始位置模3余1的后缀个数
	r[n] = r[n+1] = 0;
	for(i = 0; i < n; ++i)
		if(i%3) wa[tbc++] = i;

	//位数为3的基数排序 wa->wb
	sort(r+2, wa, wb, tbc, m);
	sort(r+1, wb, wa, tbc, m);
	sort(r, wa, wb, tbc, m);

	//合并重复，得到新的rank数组(对于模3余1与2的数)
	for(p = 1, rn[F(wb[0])]=0, i = 1; i < tbc; ++i)
		rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p-1 : p++;

	if(p < tbc)
		dc3(rn, san, tbc, p);
	else
		for(i = 0; i < tbc; ++i)
			san[rn[i]] = i;
	//得到模3余1与2的数的后缀数组

	for(i = 0; i < tbc; ++i)
		if(san[i] < tb)
			wb[ta++] = san[i] * 3;

	if(n % 3 == 1)
		wb[ta++] = n-1;

	sort(r, wb, wa, ta, m);//wb->wa for mod 3  == 0
	for(i = 0; i < tbc; ++i)
		wv[wb[i] = G(san[i])] = i;//恢复后缀数组对应位置for mod 3 == 1,2

	//接下来合并结果	
	for(i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
		sa[p] = c12(wb[j]%3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];

	while(i < ta)
		sa[p++] = wa[i++];
	while(j < tbc)
		sa[p++] = wb[j++];

}



int main()
{

}