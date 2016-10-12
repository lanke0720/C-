Test* New()  //operator new()  ->malloc -> 构造 
{
	Test* p=(Test*)mallloc(sizeof(Test));
	nuw(p) Test(0);

	return p;
}
void Delete (Test* p)  // 析构 -> operator delete() -> free
{
	if(NULL == p)
	{
		return ;
	}
	p->~Test();
	free(p);
}
Test* NEW_N(size_t count) //size+4 -> operator new[](size+4) ->operator new ->malloc ->ptr
{
	int *p =(int*)malloc(sizeof(Test*)*count+4);
	*p = count;
	Test* pret = (Test*)(++p);
	for(int idx=0; idx<count ;++idx)
	{
		new(pret+idx) Test(idx);
	}
	return pret;
}
void Delete_N(Test* p) // p向前便宜4个字节-> 渠道对象的个数count-> 调用count次 -》 析构函数-》 operator delete[]->operator delete ->free
{
	if(NULL == p)
	{
		return ;
	}
	int* pfree = (int*)((int)p-4);
	int count = *pfree;
	for(int idx=0; idx<count; ++count)
	{
		(p+free)->~Test();
	}
	free(pfree);
}
