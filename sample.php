<?php
mmseg_load_chars('data/chars.dic');
mmseg_load_words('data/words-sogou.dic');
mmseg_load_words('data/words-custom.dic');
#mmseg_load_words('data/words.dic');
$text = "安居客集团是一个专业的网上找房信息服务平台，目标是成为中国信息量最大、房源质量最好的首选网上找房市场，以及经纪人、开发商、经纪公司、业主和购房者最喜爱的房产互动社区；目前集团分为三个事业部，分别是安居客二手房事业部、爱房网新房事业部、好租网租房事业部。";

$mmseg = mmseg_algor_create($text);

while ($token = mmseg_next_token($mmseg)) {
    echo $token['text'], "|";
}

mmseg_algor_destroy($mmseg);
