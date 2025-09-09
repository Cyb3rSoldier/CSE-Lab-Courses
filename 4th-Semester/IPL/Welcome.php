<?php

$a = $_POST["email"];
$b = $_POST["password"];
$pass = "pass";

if ($b != $pass) {
    echo '<script> alert("wrong password")</script>';
} else {
    echo '<script> alert("Welcome!")</script>';
    echo "Welcome to the Home page!";
}
?>