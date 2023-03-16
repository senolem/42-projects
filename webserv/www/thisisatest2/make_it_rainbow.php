<!DOCTYPE html>
<html>
<head>
	<title>Make it Rainbow!</title>
	<meta charset="UTF-8">
	<style>
		body {
			background-color: #222;
			color: #fff;
			font-family: sans-serif;
			text-align: center;
		}
		.rainbow-text {
			border: 1px dashed #999;
			padding: 10px;
			margin-top: 20px;
			text-align: center;
			background-image: linear-gradient(to right, violet, indigo, blue, green, yellow, orange, red);
			background-clip: text;
			-webkit-background-clip: text;
			color: transparent;
		}
	</style>
</head>
<body>
	<h1>Make it Rainbow!</h1>
	<?php 
		if(isset($_POST['submit'])) {
			$text = $_POST['text'];
			$length = strlen($text);
			$result = '';
			for ($i = 0; $i < $length; $i++) {
				if ($i % 2 == 0) {
					$result .= strtoupper($text[$i]);
				} else {
					$result .= $text[$i];
				}
			}
			echo '<div class="rainbow-text">'.$result.'</div>';
		}
	?>
</body>
</html>
