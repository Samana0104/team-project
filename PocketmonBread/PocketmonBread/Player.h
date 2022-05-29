#pragma once

namespace POCKETMON
{
	enum SEAL
	{
		TYPE_1 = 0, // �̻��ؾ�
		TYPE_2, // ���̸�
		TYPE_3, // ���α�
		TYPE_4, // ��ī��
		TYPE_5, // ��״�
		TYPE_6, // �Ŀ�
		TYPE_7, // ����Ĵ�
		TYPE_8, // �ߵ�
		TYPE_9, // ��Ÿ��
		TYPE_10, // ���󵵽�
		TYPE_11, // ������
		TYPE_12, // ����
		COUNT = 12
	};
}

class Player
{
private:
	bool obtainedPocketmon[POCKETMON::COUNT] = { false };
	bool clearedStage1 = false;
	bool clearedStage2 = false;
	int obtainedBread = 0;
	bool viewingEnding = false;
public:
	explicit Player();
	~Player();

	bool hasPocketmonSeal(const POCKETMON::SEAL& sealType); // �ش� ���ϸ� ���� ������ �ִ��� ������

	void playerClearedStage1(); // �÷��̾ ��������1 Ŭ���� �� ������ ȣ�� �� �Լ� ��������1 ����
	void playerClearedStage2(); // �÷��̾ ��������2 Ŭ���� �� ������ ȣ�� �� �Լ� ��������2 ����
	void playerClearedStage3(); // �÷��̾ ��������3 Ŭ���� �� ������ ȣ�� �� �Լ� ��������3 ����

	void applyPlayerCheatMode(); // ġƮ ��� ��Ʈ�� ������

	int getObtainedBread() const; // �÷��̾� �� �� �� �ִ��� �˾Ƴ� ���� ��í ǥ�ÿ�
	int getPocketmonSealCount() const; // �� ���� �� ����� �˾Ƴ� ������

	void obtainPocketmonSeal(const POCKETMON::SEAL& pocketmonType); // �÷��̾ ��í�� ���� ���� ���� ��í��
	void usePocketmonBread(); // �÷��̾ ���ϸ� ���� ����

	bool isStage1Cleared() const; // �÷��̾ ��������2�� Ŭ���� �ƴ°�? ���� ��ư��
	bool isStage2Cleared() const; // �÷��̾ ��������3�� Ŭ���� �ƴ°�? ���� ��ư��

	bool isEndingViewed() const; // �÷��̾ �Ϲݿ����� �ô°�?

	void setViewingEnding(bool view); // �÷��̾��� �Ϲݿ��� ������ ������ true �� false �Ⱥ� 
	
};