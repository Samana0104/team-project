#pragma once

namespace POCKETMON
{
	enum SEAL
	{
		TYPE_1 = 0, // 이상해씨
		TYPE_2, // 파이리
		TYPE_3, // 꼬부기
		TYPE_4, // 피카츄
		TYPE_5, // 디그다
		TYPE_6, // 냐옹
		TYPE_7, // 고라파덕
		TYPE_8, // 야돈
		TYPE_9, // 메타몽
		TYPE_10, // 갸라도스
		TYPE_11, // 망나뇽
		TYPE_12, // 뮤츠
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

	bool hasPocketmonSeal(const POCKETMON::SEAL& sealType); // 해당 포켓몬 실을 가지고 있는지 도감용

	void playerClearedStage1(); // 플레이어가 스테이지1 클리어 할 때마다 호출 될 함수 스테이지1 전용
	void playerClearedStage2(); // 플레이어가 스테이지2 클리어 할 때마다 호출 될 함수 스테이지2 전용
	void playerClearedStage3(); // 플레이어가 스테이지3 클리어 할 때마다 호출 될 함수 스테이지3 전용

	void applyPlayerCheatMode(); // 치트 모드 인트로 전용임

	int getObtainedBread() const; // 플레이어 빵 몇 개 있는지 알아냄 메인 가챠 표시용
	int getPocketmonSealCount() const; // 실 갯수 총 몇개인지 알아냄 도감용

	void obtainPocketmonSeal(const POCKETMON::SEAL& pocketmonType); // 플레이어가 가챠를 통해 실을 얻음 가챠용
	void usePocketmonBread(); // 플레이어가 포켓몬 빵을 뜯음

	bool isStage1Cleared() const; // 플레이어가 스테이지2를 클리어 됐는가? 메인 버튼용
	bool isStage2Cleared() const; // 플레이어가 스테이지3를 클리어 됐는가? 메인 버튼용

	bool isEndingViewed() const; // 플레이어가 일반엔딩을 봤는가?

	void setViewingEnding(bool view); // 플레이어의 일반엔딩 유무를 설정함 true 봄 false 안봄 
	
};