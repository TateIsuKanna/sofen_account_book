# sofen_account_book
4人で作り途中の家計簿ソフト．

## Build and run
```
make run
```

## Usage
usage: nn [-h]

-h	このヘルプを表示します．

- ユーザー名指定 `user ユーザー名`
- 追加 `add`でaddモードに入ります. `>{. | [[年/]月/]日} 項目名 金額` 年，月は省略すると現在の日付が使われます．. は現在の日時を指定します．
- 削除 `del {* | . | [[年/]月/]日 } {* | 項目名 | [-]{><}金額}`* は全ての項目を指定します．
- 検索 `search {* | . | [[年/]月/]日 } {* | 項目名 | [-]{><}金額}` 
- 項目別収支 `rate`
- 項目別支出グラフ描画`graph`
