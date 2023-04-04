<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST')
{
    if (!empty($_POST['cookie_name']) && !empty($_POST['cookie_value']))
    {
        setcookie($_POST['cookie_name'], $_POST['cookie_value'], time() + 3600);
    }
}
?>
<!DOCTYPE html>
<html>
<head>
	<title>Cookies 🍪</title>
	<meta charset="UTF-8">
	<style>
		body {
			background-color: #222;
			color: #fff;
			font-family: sans-serif;
			text-align: center;
		}
	</style>
</head>
<body>
	<h1>Cookies 🍪</h1>
	<br>
	<h2>Create a new cookie:</h2>
<form method="post">
  <label for="cookie_name">Name:</label>
  <input type="text" name="cookie_name" id="cookie_name"><br><br>
  <label for="cookie_value">Value:</label>
  <input type="text" name="cookie_value" id="cookie_value"><br><br>
  <input type="submit" value="Create Cookie">
</form>
	<?php
if (!empty($_COOKIE))
{
    echo '<h2>Current Cookies:</h2>';
    echo '<ul>';
    foreach ($_COOKIE as $name => $value)
    {
        echo '<li>' . $name . ' = ' . $value . '</li>';
    }
    echo '</ul>';
}

?>
</body>
</html>
