<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	$inputText = $_POST['text_input'];
	$upperText = strtoupper($inputText);
	echo $upperText;
}
?>
