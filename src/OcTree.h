#pragma once
#include"tree_class.h"
#include"Voxel.h"
#include"HexActor.h"

/*
��ȡ��ʼ����
�ɻ�ȡ �����״�߽��ʼ����
���ޱ߽�ľ���/�Ǿ��Ⱥ�������
��Ӧ������3.1���ݣ���
*/


class OcTree
{
public:
	OcTree(My_Voxel& _vox, unsigned int max_lenth, unsigned int min_lenth);
	~OcTree();

	//========================================================================
	// �������ܣ� �ۺϵ��ú��������ջ�û��ִ�С������1�ĺ������ҽڵ������
	// ʹ�ò����� root����ǰ�ռ�ڵ㣻	dst����ֵ�����ͼ��	axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   �޷���ֵ
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void build_adaptive_tree();

	



private:
	//========================================================================
// �������ܣ� ����һ���Ĳ����ڵ㣬�ڵ�ռ�Ϊ������
// ʹ�ò����� x,y ���ڵ����Ͻ����꣨opencv����ϵ����	lenth���ڵ�ռ������α߳�	
//  dst�� ��ֵ�����ͼ��	location����ǰ�ڵ��ڸ��ڵ��е�λ�ã�	axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
// ����ֵ��   ���ش������½ڵ�
// �༭���ڣ� 2020/3/17
//========================================================================
	OcTreeNode* creat_node(unsigned x, unsigned y, unsigned z, unsigned lenth, string location);

	//========================================================================
	// �������ܣ� �ݹ�Ļ��ֿռ�ʹ����ڵ㣬�ڵ�ռ�Ϊ������
	// ʹ�ò����� root����ǰ�ռ�ڵ㣻	dst����ֵ�����ͼ��	axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   ���ش������½ڵ�
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void build_tree();

	//========================================================================
	// �������ܣ� �ж����ڿռ�ڵ��Ƿ����㻮������
	// ʹ�ò����� root����ǰ�ռ�ڵ㣻		axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   ���ص�bool���ж��Ƿ���Ҫ�������ֵ�ǰ�ڵ�
	// �༭���ڣ� 2020/3/17
	//========================================================================
	bool check_edge(OcTreeNode* root);

	//========================================================================
	// �������ܣ� �ݹ黮������Ľڵ�ռ䣬��֤���ڿռ仮�ֶ����1
	// ʹ�ò����� root����ǰ�ռ�ڵ㣻		axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   �޷���ֵ
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void adapted_hexahedral(OcTreeNode* root);


	//========================================================================
	// �������ܣ� ����һ���Ĳ����ڵ㣬�ڵ�ռ�Ϊ������
	// ʹ�ò����� x,y ���ڵ����Ͻ����꣨opencv����ϵ����	lenth���ڵ�ռ������α߳�	
	//  dst�� ��ֵ�����ͼ��	location����ǰ�ڵ��ڸ��ڵ��е�λ�ã�	axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   ���ش������½ڵ�
	// �༭���ڣ� 2020/3/17
	//========================================================================
	OcTreeNode* creat_full_node(unsigned x, unsigned y, unsigned z, unsigned lenth, string location);


	//========================================================================
	// �������ܣ� �������ڵ㣬���ǵ�ǰ�ռ�ȫ������
	// ʹ�ò����� root����ǰ�ռ�ڵ㣻		axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   �޷���ֵ
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void build_full_node(OcTreeNode* root);

	//========================================================================
	// �������ܣ� ���ù�������㷨������������ϵݹ黮��
	// ʹ�ò����� last����һ��ݹ����õķǿսڵ㣻		axis���ռ�����������ڼ�¼���ж��ڵ�ռ�Ļ������
	// ����ֵ��   �޷���ֵ
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void layer_traversal(vector<OcTreeNode*>* last);

	//========================================================================
	// �������ܣ� ȡ������Ҷ�ӽڵ㣬������ʾģ�͵������嵥Ԫ
	// ʹ�ò����� src ��ͼ��
	// ����ֵ��   �����޷�������
	// �༭���ڣ� 2020/3/17
	//========================================================================
	void get_leaf_node(OcTreeNode* root);

	//========================================================================
	// �������ܣ� ������С�� ����ͼ�񳤿����ֵ�� 2��ָ����������
	// ʹ�ò����� src ��ͼ��
	// ����ֵ��   �����޷�������
	// �༭���ڣ� 2020/3/17
	//========================================================================
	unsigned int get_max_hex();


	//��������ϵ����񣬽���������������ٻ���
	void m_subdivision(vector<Hexahedral3D*>& nodes, My_Voxel vox);

	//�Ѷ�Ӧ���������Լ��뵽�����У�����ת��Ϊtxt�������
	void Addnodes(int index,Hexahedral3D* m_node);

public:
	OcTreeNode* root;
	vector<vector<vector<bool>>>axis;
	////��vector<OcTreeNode*>����vector<hexahedral*>
	//vector<OcTreeNode*> nodes;//��ǰ
	vector<Hexahedral3D*> nodes; //���������

	//�����м��ֲ��ϵĴ����������飬����������Ϊtxt
	vector<Hexahedral3D*> m_node1;
	vector<Hexahedral3D*> m_node2;
	vector<Hexahedral3D*> m_node3;
private:
	My_Voxel& vox;
	//Mat& dst;
	//Mat& src;
	unsigned int max_lenth; //��������ֵ
	unsigned int min_lenth; //�������Сֵ
	//����������ֵ����Сֵһ������˵�����ֵ��Ǿ�������
};