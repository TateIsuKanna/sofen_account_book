# sofen_account_book
4人で作り途中の家計簿ソフト．

## Required
[gnuplot](http://www.gnuplot.info/)

## Build and run
```
make run
```

## Usage
1. ユーザー名指定 `user ユーザー名`
1. 追加 `add [[年/]月/]日 項目名 金額` 年，月は省略すると現在の日付が使われる．
1. 削除 `del 項目名`
1. 検索 `search 項目名` 
1. 項目別収支 `rate`
1. 項目別支出グラフ描画`graph`
