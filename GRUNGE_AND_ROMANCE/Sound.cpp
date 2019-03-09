//====================================================================================================================================================================================
// 概要
// ファイル名：Sound.cpp
// コーディングフォント：Ricty Diminished( 16サイズ )
// 作成者：HAL東京 GP-11B-341 07 亀岡竣介
// 作成日：2018/12/10
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// インクルード
//====================================================================================================================================================================================
#include "main.h"
#include "Sound.h"
//====================================================================================================================================================================================
// グローバル変数
//====================================================================================================================================================================================
SOUND Sound_State;
//====================================================================================================================================================================================
// 領域 - 取得
//====================================================================================================================================================================================
#pragma region Initialize
//====================================================================================================================================================================================
// サウンドの初期化
// 関数名：HRESULT Initialize_Sound
// 戻り値：HRESULT
// 引数 1：HWND
//====================================================================================================================================================================================
HRESULT Initialize_Sound(HWND Window_Handle)
{
	// 初期化 / ゼロクリア
	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Play_Flag[i] = NULL;
		ZeroMemory(&Sound_State.Sound_Buffer[i], sizeof(LPDIRECTSOUNDBUFFER8));
	}

	// IDirectSound8オブジェクトの作成
	if (FAILED(DirectSoundCreate8	//	DirectSoundCreate8関数："IDirectSound8"インターフェイスをサポートするオブジェクトを作成し、初期化する
	(
		NULL,						//	サウンドデバイスを示すGUIDのアドレス：NULL = システム全体の既定のオーディオ再生デバイスを指定
		&Sound_State.Direct_Sound,	//	"IDirectSound8"インターフェイスポインタを受け取る変数のアドレス
		NULL						//	コンポーネントオブジェクトモデル( COM )集成に対する制御オブジェクトのIUnknownインターフェイスのアドレスへのポインタ：インターフェイスが集成されていない場合には"NULL"( 通常、呼び出し側は"NULL"を渡す )
	)))
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CREATE_SOUND);
	}

	// 協調モードを設定( フォアグラウンド&非排他モード )
	if (FAILED(Sound_State.Direct_Sound->SetCooperativeLevel	//	SetCooperativeLevel関数：アプリケーションの最上位動作を決定する
	(
		Window_Handle,	//	ウィンドウハンドル
		DSSCL_PRIORITY	//	動作を指定( DSSCL_PRIORITY：優先レベルに設定する )
	)))
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_SETTING_COOPERATION_MODE);
	}

	// サウンドの読み込み
	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Sound_Buffer[i] = Load_Sound(i);
	}

	// 正常終了
	return S_OK;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 解放
//====================================================================================================================================================================================
#pragma region Release
//====================================================================================================================================================================================
// サウンドの解放
// 関数名：void Release_Sound
// 戻り値：void
//====================================================================================================================================================================================
void Release_Sound(void)
{
	//Start_Critical_Section();
	SAFE_RELEASE(Sound_State.Direct_Sound);
	//End_Critical_Section();

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 更新
//====================================================================================================================================================================================
#pragma region Update
//====================================================================================================================================================================================
// サウンドの更新
// 関数名：void Update_Sound
// 戻り値：void
//====================================================================================================================================================================================
void Update_Sound(void)
{
	// フェード処理
	for (int i = 0; i < SOUND_MAX; i++)
	{
		if ((Sound_State.Fade_Type[i] != SOUND_FADE_TYPE_NONE) && (Sound_State.Fade_Type[i] == SOUND_FADE_TYPE_FADE_IN))
		{
			// フェードイン
			Update_Sound_Fade_In(i);
		}
		else if ((Sound_State.Fade_Type[i] != SOUND_FADE_TYPE_NONE) && (Sound_State.Fade_Type[i] == SOUND_FADE_TYPE_FADE_OUT))
		{
			// フェードアウト
			Update_Sound_Fade_Out(i);
		}
	}

	return;
}

//====================================================================================================================================================================================
// サウンドの更新( フェードイン )
// 関数名：void Update_Sound_Fade_In
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Update_Sound_Fade_In(int Sound_Index)
{
	// 早期リターン
	if (!Sound_State.Fade_Switch[Sound_Index])
	{
		return;
	}

	if (Sound_State.Setting_Volume.Max <= Sound_State.Volume[Sound_Index])
	{
		// 音量の設定
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Volume[Sound_Index] += SOUND_FADE_VALUE;

	if (Sound_State.Setting_Volume.Max > Sound_State.Volume[Sound_Index])
	{
		// 音量の設定
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Fade_Switch[Sound_Index] = false;
	Sound_State.Fade_Type[Sound_Index] = SOUND_FADE_TYPE_NONE;
	Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Max;

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);

	// 音量の設定
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}

//====================================================================================================================================================================================
// サウンドの更新( フェードアウト )
// 関数名：void Update_Sound_Fade_Out
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Update_Sound_Fade_Out(int Sound_Index)
{
	// 早期リターン
	if (!Sound_State.Fade_Switch[Sound_Index])
	{
		return;
	}

	if (Sound_State.Setting_Volume.Min >= Sound_State.Volume[Sound_Index])
	{
		// 音量の設定
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Volume[Sound_Index] -= SOUND_FADE_VALUE;

	if (Sound_State.Setting_Volume.Min < Sound_State.Volume[Sound_Index])
	{
		// 音量の設定
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	Sound_State.Fade_Switch[Sound_Index] = false;
	Sound_State.Fade_Type[Sound_Index] = SOUND_FADE_TYPE_NONE;
	Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Min;
	Stop_Sound(Sound_Index);

	// 音量の設定
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 読み込み
//====================================================================================================================================================================================
#pragma region Load
//====================================================================================================================================================================================
// サウンドの読み込み
// 関数名：LPDIRECTSOUNDBUFFER8 Load_Sound
// 戻り値：LPDIRECTSOUNDBUFFER8
// 引数 1：int
//====================================================================================================================================================================================
LPDIRECTSOUNDBUFFER8 Load_Sound(int Sound_Index)
{
	// 変数宣言：初期化 / サウンド読み込み
	const char *Sound_File[] =	//	サウンドファイル
	{
		SOUND_FILE_AGONY,	//	SOUND_TYPE_AGONY
	};

	// 変数宣言：初期化
	// MMIO：マルチメディアインプット/アウトプット( マルチメディアI/O( 入出力 ) )の略称
	// .wavファイルは、リフ( RIFF )というフォーマット形式に従っている( RIFF：Resource InterChange File Format )
	// これはチャンク( Chunk：塊 )と呼ばれるデータの一まとまりを並べて音の情報を整理している
	LPDIRECTSOUNDBUFFER Sound_Base_Buffer = NULL;	//	音源データの総合バッファ
	LPDIRECTSOUNDBUFFER8 Sound_Buffer = NULL;		//	音源データのバッファ
	DSBUFFERDESC Sound_Buffer_Config;				//	バッファの設定構造体
	HMMIO MultiMedia_Input_Output_Handle = NULL;	//	マルチメディアI/Oハンドル
	MMIOINFO MultiMedia_Input_Output_Data;			//	マルチメディアI/Oのデータ構造体
	MMRESULT MultiMedia_Input_Output_Result = NULL;	//	マルチメディア処理結果を格納する変数
	MMCKINFO Riff_Chunk;							//	チャンクデータの構造体
	MMCKINFO Format_Chunk;							//	チャンクデータの構造体
	MMCKINFO Data_Chunk;							//	チャンクデータの構造体
	DWORD Data_Size = NULL;							//	データのサイズを格納する変数
	WAVEFORMATEX Pulse_Code_Modulation;				//	音源データのフォーマット構造体
	LPVOID Secondary_Buffer = NULL;					//	セカンダリバッファのデータの書き込み先アドレス
	DWORD Secondary_Buffer_Size = NULL;				//	セカンダリバッファのサイズ

	// １．マルチメディアI/Oハンドルを元に音源ファイルを開く
	memset	//	memset関数：指定されたポインタが指すオブジェクトの先頭から、指定されたバイト数分に、指定した文字データを書き込むはたらきをする( ポインタが指しているメモリから各"1"バイトごとに文字をセットする )
	(
		&MultiMedia_Input_Output_Data,	//	セット先のメモリブロックアドレス ( セットする領域( ポインタ / メモリ )
		0,								//	セット元のメモリブロックアドレス ( セットする値 )
		sizeof(MMIOINFO)				//	セット元から、セット先にセットするメモリのブロックサイズを指定	( セットするサイズ )
	);
	MultiMedia_Input_Output_Handle = mmioOpen	//	mmioOpen関数：入出力のバッファリングを解除するか、入出力をバッファリングしてファイルを開く。開くことができるファイルは、標準ファイル・メモリファイル・またはカスタムの格納システム
	(
		(LPSTR)Sound_File[Sound_Index],	//	開くファイルのファイル名が入った文字列のアドレスを指定
		&MultiMedia_Input_Output_Data,	//	mmioOpen関数で使われる追加のパラメータが入った、MMIOINFO構造体のアドレスを指定
		MMIO_READ						//	オープン操作のためのフラグを指定( MMIO_READ：ファイルを読み取り専用として開く )
	);
	if (!MultiMedia_Input_Output_Handle)
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_SOUND_FILE_INPUT);
	}

	// ２．ファイルの解析( 1 ) RIFFチャンクの検索
	// 検索ワードを指定
	Riff_Chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
															//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	// キーワードを対象に検索
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend関数：mmioOpen関数で開いたRIFFファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているRIFFファイルのファイルハンドルを指定
		&Riff_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		NULL,							//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDRIFF					//	検索フラグを指定( MMIO_FINDRIFF：チャンク識別子が"RIFF"で、指定されたフォームタイプのチャンクを検索する )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// ３．ファイルの解析( 2 ) フォーマットチャンクの検索
	// 検索ワードを指定
	Format_Chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
														//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	// キーワードを対象に検索
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend関数：mmioOpen関数で開いたフォーマットファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているフォーマットファイルのファイルハンドルを指定
		&Format_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		&Riff_Chunk,					//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDCHUNK					//	検索フラグを指定( MMIO_FINDCHUNK：指定されたチャンク識別子のチャンクを検索します )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// 検索情報を元に読み込み処理
	Data_Size = mmioRead	//	mmioRead関数：mmioOpen関数で開いたファイルから、指定されたバイト数を読み取る
	(
		MultiMedia_Input_Output_Handle,	//	読み取るファイルのファイルハンドルを指定
		(HPSTR)&Pulse_Code_Modulation,	//	ファイルから読み取られたデータが入るバッファのアドレスを指定
		Format_Chunk.cksize				//	ファイルから読み取るバイト数を指定
	);
	// 読み込みに失敗したら異常終了
	if (Data_Size != Format_Chunk.cksize)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_LOAD_SOUND_FILE_HANDLE);
	}

	mmioAscend	//	mmioAscend関数：mmioDescend関数で進入した、またはmmioCreateChunk関数で作成したRIFFファイルのチャンクから退出する
	(
		MultiMedia_Input_Output_Handle,	//	開いているRIFFファイルのファイルハンドルを指定
		&Format_Chunk,					//	mmioDescend関数または、mmioCreateChunk関数で値が書き込まれているアプリケーション定義のMMCKINFO構造体のアドレスを指定
		0								//	予約されているので、"0"を指定
	); 

	// ４．ファイルの解析( 3 ) データチャンクの検索
	// 検索ワードを指定
	Data_Chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
														//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	MultiMedia_Input_Output_Result = mmioDescend		//	mmioDescend関数：mmioOpen関数で開いたフォーマットファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているフォーマットファイルのファイルハンドルを指定
		&Data_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		&Riff_Chunk,					//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDCHUNK					//	検索フラグを指定( MMIO_FINDCHUNK：指定されたチャンク識別子のチャンクを検索します )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// ５．データの読み込み
	// ポインタ変数宣言：初期化
	char *Data = new char[Data_Chunk.cksize];	//	必要な大きさの領域を確保して

	Data_Size = mmioRead	//	mmioRead関数：mmioOpen関数で開いたファイルから、指定されたバイト数を読み取る
	(
		MultiMedia_Input_Output_Handle,	//	読み取るファイルのファイルハンドルを指定
		(HPSTR)Data,					//	ファイルから読み取られたデータが入るバッファのアドレスを指定
		Data_Chunk.cksize				//	ファイルから読み取るバイト数を指定
	);
	// データの読み込みに失敗したら異常終了
	if (Data_Size != Data_Chunk.cksize)
	{
		// 削除
		delete[] Data;

		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_LOAD_SOUND_FILE_HANDLE);
	}

	// ６．音源データを読み込む「セカンダリバッファ」を用意
	ZeroMemory(&Sound_Buffer_Config, sizeof(DSBUFFERDESC));	//	ZeroMemoryマクロ：指定した変数の中身を"0"クリアするマクロ

	// 各種設定
	// DSBUFFERDESC：新しいバッファオブジェクトの特性を記述する
	Sound_Buffer_Config.dwSize = sizeof(DSBUFFERDESC);	//	構造体のサイズ( 単位：byte )を指定：構造体を使う前に、このメンバを初期化しなければならない
	Sound_Buffer_Config.dwFlags =						//	バッファの能力を示すフラグ
		(
			DSBCAPS_GETCURRENTPOSITION2 |
			DSBCAPS_GLOBALFOCUS |
			DSBCAPS_LOCDEFER |
			DSBCAPS_CTRLFX |
			DSBCAPS_CTRLVOLUME
		);
	Sound_Buffer_Config.dwBufferBytes = Data_Size;				//	新しいバッファのサイズ( 単位：byte )を指定
	Sound_Buffer_Config.lpwfxFormat = &Pulse_Code_Modulation;	//	バッファのウェーブフォームフォーマットを指定

	// 総合バッファを作成
	if (FAILED(Sound_State.Direct_Sound->CreateSoundBuffer	//	CreateSoundBuffer関数：サンプリングオーディオを管理するために、サウンドバッファオブジェクトを作成する
	(
		&Sound_Buffer_Config,	//	作成するサウンドバッファが記述されている"DSBUFFERDESC"構造体のアドレス
		&Sound_Base_Buffer,		//	新しいバッファオブジェクトの"IDirectSoundBuffer"インターフェイスを受け取る変数のアドレス
		NULL					//	コンポーネントオブジェクトモデル( COM )集成に対する制御オブジェクトのIUnknownインターフェイスのアドレスへのポインタ。インターフェイスが集成されていない場合には"NULL" // 通常、呼び出し側は"NULL"を渡す
	)))
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CREATE_SOUND_BUFFER);
	}

	// サウンドバッファの取り出し
	if (FAILED(Sound_Base_Buffer->QueryInterface	//	QueryInterface関数：オブジェクトが特定のコンポーネントオブジェクトモデル( COM )インターフェイスをサポートしているかどうかを判別する
													//						インターフェイスがサポートされている場合、システムはオブジェクトの参照カウントを増やし、アプリケーションはそのインターフェイスをすぐに使える
	(
		IID_IDirectSoundBuffer8,	//	要求するインターフェイスの参照識別子
		(LPVOID*)&Sound_Buffer		//	目的のインターフェイスがサポートされている場合に、インターフェイスへのポインタが格納されるポインタ変数のアドレス
	)))
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_GET_SOUND_INTERFACE);
	}

	// サウンドバッファ取り出し後、総合バッファを削除
	//Start_Critical_Section();
	SAFE_RELEASE(Sound_Base_Buffer);
	//End_Critical_Section();

	// ７．用意したセカンダリバッファにデータを転送
	// 書き込み可能にするため、バッファをロック
	if (FAILED(Sound_Buffer->Lock	//	Lock関数：デッドロックなしですべての引数をロックする
	(
		0,
		0,
		&Secondary_Buffer,
		&Secondary_Buffer_Size,
		NULL,
		NULL,
		DSBLOCK_ENTIREBUFFER
	)))
	{
		// エラーメッセージの出力
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_ARGUMENT_LOCK);
	}

	// データの転送
	memcpy	//	memcpy関数：第2引数( コピー元 )から、第3引数( 指定サイズ )分、第1引数( コピー先 )へメモリをコピーする
	(
		Secondary_Buffer,		//	コピー先のメモリブロックアドレス
		Data,					//	コピー元のメモリブロックアドレス
		Secondary_Buffer_Size	//	コピー元から、コピー先にコピーするメモリのブロックサイズを指定
	);

	// 元の読み込み領域を削除
	delete[] Data;

	// バッファのロックを解除
	Sound_Buffer->Unlock	//	Unlock関数：レコードのロックを解除する
	(
		Secondary_Buffer,
		Secondary_Buffer_Size,
		0,
		0
	);

	// セカンダリバッファを戻り値として返す
	return Sound_Buffer;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 再生
//====================================================================================================================================================================================
#pragma region Play
//====================================================================================================================================================================================
// サウンドの再生
// 関数名：void Play_Sound
// 戻り値：void
// 引数 1：int
// 引数 2：int
//====================================================================================================================================================================================
void Play_Sound(int Sound_Index, int Play_Method)
{
	// Sound_Flag："1" = ( E_DS8_FLAG_LOOP )ならループ再生
	if (!Sound_State.Pause_Flag[Sound_Index])
	{
		Sound_State.Sound_Buffer[Sound_Index]->SetCurrentPosition(0);
		Sound_State.Sound_Buffer[Sound_Index]->Play(0, 0, Play_Method);
	}
	else
	{
		Sound_State.Sound_Buffer[Sound_Index]->SetCurrentPosition(Sound_State.Play_Position[Sound_Index]);
		Sound_State.Sound_Buffer[Sound_Index]->Play(0, 0, Play_Method);
	}

	Sound_State.Play_Method[Sound_Index] = Play_Method;
	Sound_State.Play_Flag[Sound_Index] = true;
	Sound_State.Pause_Flag[Sound_Index] = false;

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 一時停止
//====================================================================================================================================================================================
#pragma region Pause
//====================================================================================================================================================================================
// サウンドの一時停止
// 関数名：void Pause_Sound
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Pause_Sound(int Sound_Index)
{
	if (Sound_State.Play_Flag[Sound_Index])
	{
		Sound_State.Pause_Flag[Sound_Index] = true;
		Get_Play_Position_Sound(Sound_Index);
	}
	else
	{
		Sound_State.Pause_Flag[Sound_Index] = false;
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 停止
//====================================================================================================================================================================================
#pragma region Stop
//====================================================================================================================================================================================
// サウンドの停止
// 関数名：void Stop_Sound
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Stop_Sound(int Sound_Index)
{
	// 変数宣言：初期化
	DWORD Status = NULL;	//	ステータス

	Sound_State.Sound_Buffer[Sound_Index]->GetStatus(&Status);	//	GetStatus関数：指定されたCFileオブジェクトインスタンス、または指定されたファイルパスに関連したステータス情報を取得します
	
	// サウンド再生中
	if (Status & DSBSTATUS_PLAYING)
	{
		Sound_State.Sound_Buffer[Sound_Index]->Stop();	//	Stop関数：現在の表現式の実行を中断する( 内容としては、"Pause"のようなもの )
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 調査
//====================================================================================================================================================================================
#pragma region Check
//====================================================================================================================================================================================
// サウンドの再生状態を調査
// 関数名：bool Check_Play_Flag_Sound
// 戻り値：bool
// 引数 1：int
//====================================================================================================================================================================================
bool Check_Play_Flag_Sound(int Sound_Index)
{
	// 変数宣言：初期化
	DWORD Status = NULL;	//	ステータス

	Sound_State.Sound_Buffer[Sound_Index]->GetStatus(&Status);	//	GetStatus関数：指定されたCFileオブジェクトインスタンス、または指定されたファイルパスに関連したステータス情報を取得します
	
	// サウンド再生中
	if (Status & DSBSTATUS_PLAYING)
	{
		return true;
	}

	return false;
}

//====================================================================================================================================================================================
// サウンドの再生状態を調査( 全て )
// 関数名：void Check_Play_Flag_All_Sound
// 戻り値：void
//====================================================================================================================================================================================
void Check_Play_Flag_All_Sound(void)
{
	// 変数宣言：初期化
	DWORD Status = NULL;	//	ステータス

	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Sound_Buffer[i]->GetStatus(&Status);	//	GetStatus関数：指定されたCFileオブジェクトインスタンス、または指定されたファイルパスに関連したステータス情報を取得します
		
		if (Status & DSBSTATUS_PLAYING)
		{
			Sound_State.Play_Flag[i] = true;
		}
		else
		{
			Sound_State.Play_Flag[i] = false;
		}

		Status = NULL;
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 設定
//====================================================================================================================================================================================
#pragma region Set
//====================================================================================================================================================================================
// サウンドの一時停止設定
// 関数名：void Set_Pause_Sound
// 戻り値：void
//====================================================================================================================================================================================
void Set_Pause_Sound(void)
{
	for (int i = 0; i < SOUND_MAX; i++)
	{
		//switch (i)
		//{
		////case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
		////case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
		////case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
		////case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
		////case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
		////case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
		////case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
		////case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
		//	Pause_Sound(i);
		//	Stop_Sound(i);
		//	continue;
		//	break;
		//default:
		//	continue;
		//	break;
		//}
	}

	return;
}

//====================================================================================================================================================================================
// サウンドの再生再開設定
// 関数名：void Set_Re_Play_Sound
// 戻り値：void
//====================================================================================================================================================================================
void Set_Re_Play_Sound(void)
{
	for (int i = 0; i < SOUND_MAX; i++)
	{
		// 早期コンティニュー
		if (!Sound_State.Pause_Flag[i])
		{
			continue;
		}

		//switch (i)
		//{
		//case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
		//case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
		//case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
		//case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
		//case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
		//case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
		//case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
		//case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
		//	Play_Sound(i, Sound_State.Play_Method[i]);
		//	continue;
		//	break;
		//default:
		//	continue;
		//	break;
		//}
	}

	return;
}

//====================================================================================================================================================================================
// サウンドのフェード設定
// 関数名：void Set_Sound_Fade
// 戻り値：void
// 引数 1：int
// 引数 2：int
//====================================================================================================================================================================================
void Set_Sound_Fade(int Sound_Index, int Sound_Fade_Type)
{
	if (Sound_Fade_Type == SOUND_FADE_TYPE_NONE)
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	}
	else
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, true);
	}

	Sound_State.Fade_Type[Sound_Index] = Sound_Fade_Type;
	Sound_State.Fade_Switch[Sound_Index] = true;

	return;
}

//====================================================================================================================================================================================
// サウンドの音量設定
// 関数名：void Set_Sound_Volume
// 戻り値：void
// 引数 1：int
// 引数 2：int
//====================================================================================================================================================================================
void Set_Sound_Volume(int Sound_Index, int Sound_Volume_Type)
{
	Set_Sound_Fade(Sound_Index, SOUND_FADE_TYPE_NONE);

	switch (Sound_Volume_Type)
	{
	case SOUND_VOLUME_TYPE_LOWEST:
		Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Min;
		break;
	case SOUND_VOLUME_TYPE_HIGHEST:
		Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Max;
		break;
	default:
		break;
	}

	// 音量の設定
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// 領域 - 取得
//====================================================================================================================================================================================
#pragma region Get
//====================================================================================================================================================================================
// サウンドの再生位置の取得
// 関数名：void Get_Play_Position_Sound
// 戻り値：void
// 引数 1：int
//====================================================================================================================================================================================
void Get_Play_Position_Sound(int Sound_Index)
{
	Sound_State.Sound_Buffer[Sound_Index]->GetCurrentPosition(&Sound_State.Play_Position[Sound_Index], NULL);

	return;
}

//====================================================================================================================================================================================
// サウンドの取得
// 関数名：SOUND *Get_Sound
// 戻り値：SOUND
//====================================================================================================================================================================================
SOUND *Get_Sound(void)
{
	return &Sound_State;
}
#pragma endregion
////====================================================================================================================================================================================
//// 領域 - デバッグ
////====================================================================================================================================================================================
//#pragma region Debug
//#ifdef _DEBUG
////====================================================================================================================================================================================
//// サウンドのデバッグ描画
//// 関数名：void Draw_Debug_Sound
//// 戻り値：void
//// 引数 1：DEBUG*
////====================================================================================================================================================================================
//void Draw_Debug_Sound(DEBUG *Debug)
//{
//	// 早期リターン
//	if ((!Debug->Switch) || (Debug->Type != DEBUG_TYPE_SOUND))
//	{
//		return;
//	}
//
//	// デバッグタイプ
//	Print_Debug("==========| サウンド |========== \n\n");
//	// 設定音量
//	Print_Debug("Setting_Volume.Min：%d \n", Sound_State.Setting_Volume.Min);
//	Print_Debug("Setting_Volume.Max：%d \n\n", Sound_State.Setting_Volume.Max);
//	// 再生フラグ・サウンド音量
//	switch (Get_Progress())
//	{
//	case PROGRESS_TYPE_OPENING:
//		Draw_Debug_Sound_Opening();
//		break;
//	case PROGRESS_TYPE_TITLE:
//		Draw_Debug_Sound_Title();
//		break;
//	case PROGRESS_TYPE_GAME:
//		Draw_Debug_Sound_Game();
//		break;
//	case PROGRESS_TYPE_ENDING:
//		Draw_Debug_Sound_Ending();
//		break;
//	default:
//		break;
//	}
//	// 終了
//	Print_Debug("==========| 終了 |==========");
//
//	return;
//}
//
////====================================================================================================================================================================================
//// サウンド( オープニング )のデバッグ描画
//// 関数名：void Draw_Debug_Sound_Opening
//// 戻り値：void
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Opening(void)
//{
//	// 変数宣言：初期化
//	char Debug_Play_Flag[SOUND_MAX][6];		//	フラグ識別
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	フラグ識別
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	フラグ識別
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// 早期コンティニュー
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// 再生フラグ
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// 一時停止フラグ
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// フェードスイッチ
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_SOUND_EFFECT_000_OPENING_NOISE:
//			Print_Debug("[ SE_000 - NOISE ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_OPENING_RECORD_NOISE:
//			Print_Debug("[ SE_001 - RECORD_NOISE ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// サウンド( タイトル )のデバッグ描画
//// 関数名：void Draw_Debug_Sound_Title
//// 戻り値：void
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Title(void)
//{
//	// 変数宣言：初期化
//	char Debug_Play_Flag[SOUND_MAX][6];		//	フラグ識別
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	フラグ識別
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	フラグ識別
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// 早期コンティニュー
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// 再生フラグ
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// 一時停止フラグ
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// フェードスイッチ
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_BACKGROUND_MUSIC_000_TITLE_AMBIENT:
//			Print_Debug("[ BGM_000 - AMBIENT ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_000_TITLE_DECISION:
//			Print_Debug("[ SE_000 - DECISION ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_TITLE_SELECT:
//			Print_Debug("[ SE_001 - SELECT ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_TITLE_NEXT:
//			Print_Debug("[ SE_002 - NEXT ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// サウンド( ゲーム )のデバッグ描画
//// 関数名：void Draw_Debug_Sound_Game
//// 戻り値：void
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Game(void)
//{
//	// 変数宣言：初期化
//	char Debug_Play_Flag[SOUND_MAX][6];		//	フラグ識別
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	フラグ識別
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	フラグ識別
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// 早期コンティニュー
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// 再生フラグ
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// 一時停止フラグ
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// フェードスイッチ
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_BACKGROUND_MUSIC_000_GAME_FOREST:
//			Print_Debug("[ BGM_000 - FOREST ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_BACKGROUND_MUSIC_001_GAME_AMBIENT:
//			Print_Debug("[ BGM_001 - AMBIENT ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
//			Print_Debug("[ BGM_002 - PARTICLE ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_000_GAME_BELL:
//			Print_Debug("[ SE_000 - BELL ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK:
//			Print_Debug("[ SE_001 - WALK ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN:
//			Print_Debug("[ SE_002 - RUN ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
//			Print_Debug("[ SE_003 - THE_TOPOS ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
//			Print_Debug("[ SE_004 - VOEZ ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
//			Print_Debug("[ SE_005 - LUMINA ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
//			Print_Debug("[ SE_006 - DEVISION ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_007_GAME_PAUSE:
//			Print_Debug("[ SE_007 - PAUSE ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
//			Print_Debug("[ SE_008 - MENU ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
//			Print_Debug("[ SE_009 - MENU_ENTER ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
//			Print_Debug("[ SE_010 - MENU_BACK ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_011_GAME_TUTORIAL_SUCCESS:
//			Print_Debug("[ SE_011 - TUTORIAL_SUCCESS ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_012_GAME_TUTORIAL_CHECK:
//			Print_Debug("[ SE_012 - TUTORIAL_CHECK ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_013_GAME_TUTORIAL_PAPER:
//			Print_Debug("[ SE_013 - TUTORIAL_PAPER ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// サウンド( エンディング )のデバッグ描画
//// 関数名：void Draw_Debug_Sound_Ending
//// 戻り値：void
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Ending(void)
//{
//	// 変数宣言：初期化
//	char Debug_Play_Flag[SOUND_MAX][6];		//	フラグ識別
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	フラグ識別
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	フラグ識別
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// 早期コンティニュー
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// 再生フラグ
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// 一時停止フラグ
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// フェードスイッチ
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_SOUND_EFFECT_000_ENDING_SPLASH:
//			Print_Debug("[ SE_000 - SPLASH ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_ENDING_DEEP:
//			Print_Debug("[ SE_001 - DEEP ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_ENDING_SIGNAL:
//			Print_Debug("[ SE_002 - SIGNAL ] \n");
//			Print_Debug("Play_Method：%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position：%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type：%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume：%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag：%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag：%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch：%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//#endif
//#pragma endregion