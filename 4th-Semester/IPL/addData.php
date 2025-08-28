
<?php
function greet($name, $age) {
    return "Hello! My name is $name and I am $age years old.";
}

$message = '';
if ($_SERVER['REQUEST_METHOD'] == 'POST' && $_POST['res'] == 'add') {
    $name = $_POST['name'];
    $age = $_POST['age'];
    $message = greet($name, $age);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Add your data</title>
</head>
<body>

<form method="post">
    <input type="text" name="name" placeholder="Enter your name"><br><br>
    <input type="number" name="age" placeholder="Enter your age"><br><br>
    <button type="submit" name="res" value="add">Add</button>
</form>

<p><?= $message ?></p>


</body>
</html>