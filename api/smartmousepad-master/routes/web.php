<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

use Illuminate\Support\Facades\Mail;
use App\Mail\TestMail;

Route::get('/', function () {

  return view('welcome');

});
Route::get('check-queue', function(){

  Mail::to('paardekooper.robert@gmail.com')->send(new TestMail());

  return 'Working';

});
