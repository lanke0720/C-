////�����ӡ������
//
////001
//
//void PrintListRever(ListNode* pHead)
//{
//	stack<ListNode*> node;
//	ListNode* pNode = pHead;
//	while (pNode != NULL)
//	{
//		node.push(pNode);
//		pNode = pNode->_next;
//	}
//
//	while (!node.empty())
//	{
//		pNode = node.top();
//		cout<<pNode->_value<<" ";
//		node.pop();
//	}
//	
//}  //��ջ����ѭ�����µĴ���³����Ҫ��һЩ
//
//void PrintListR_R(ListNode* pHead)
//{
//	if (pHead != NULL)
//	{
//		if (pHead->next != NULL)
//		{
//			PrintListR_R(pHead->_next);
//		}
//		cout<<pHead->_value<<" ";
//	}
//}
//  �ݹ���Ȼ��������࣬���ǵ�����ǳ�����ʱ�򣬵ݹ���Ⱥܸߣ��Ӷ����ܵ��º�������ջ�����






