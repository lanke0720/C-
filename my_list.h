////逆序打印单链表
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
//}  //用栈基于循环试下的代码鲁邦性要好一些
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
//  递归虽然看起来简洁，但是当链表非常长的时候，递归深度很高，从而可能导致函数调用栈溢出。






