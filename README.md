# WaveTableSynthesizer for STM32H755

## 概要
本プロジェクトの目的は、STM32H755用のWaveTableSynthesizerを作成することです。  
WaveTableSynthesizerはリアルタイムでMIdi信号を受信し、発音する機能を持ちます。

## 使用ハードウェア
- MCU：STM32H755ZI NUCLEO
- DAC：PCM5102A
- Display：SSD1306 OLED

## シンセサイザー機能
### WaveTableによる発音
- WaveTable数：1
- 同時発音数：8
- モノラル出力

### MIDI受信
- Midiチャンネル数：1

### その他
- ADSRによる音量制御 

## GUI画面の種別
- ADSRパラメータ値の変更画面

## 特徴
### デュアルコア構成
- M7側はDSP処理を実行
- M4側はGUI処理を実行

## 開発環境
- STM32CubeIDE 1.19.0

## ビルド手順  
1.STM32CubeIDEでプロジェクトをインポート  
2.Build→Flash

## 参考にさせて頂いたサイトやリポジトリ
- ソフトウェアシンセサイザーを作る  
 https://qiita.com/agehama_/items/7da430491400e9a2b6a7

- stm32-SSD1306  
 https://github.com/afiskon/stm32-ssd1306/tree/master

- [STM32F7で作る自作MIDI音源]  
 https://www.keshikan.net/gohantabeyo/?p=283

## 今後の予定
- テーブル種別の追加
- ユニゾン機能追加
- グライド機能追加
- 周波数スペクトラルの画面表示
- エフェクト機能追加

## ライセンス
MIT License
詳細はLICENSE.txtを参照してください。
