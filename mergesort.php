<?php
function alMerge($arrA, $arrB){
	$arrC = array();
	while(count($arrA) && count($arrB)){
		$arrC[] = $arrA[0] > $arrB[0] ? array_shift($arrB) : array_shift($arrA);
	}
	return array_merge($arrC, $arrA, $arrB);
}

function mergeSort($arr){
	$len = count($arr);
	if($len <= 1){
		return $arr;
	}
	$mid = intval($len/2);
	$leftArr = mergeSort(array_slice($arr, 0, $mid));
	$rightArr = mergeSort(array_slice($arr, $mid));
	$arr = alMerge($leftArr, $rightArr);
	return $arr;
}

$arr = array(4,3,6,1,7,2,9);
print_r(mergeSort($arr));

?>
