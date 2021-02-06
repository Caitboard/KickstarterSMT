<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\UserController;
use App\Http\Controllers\EventController;
use App\Http\Controllers\GroupController;
use App\Http\Controllers\UserEventController;
/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::get('/user/{user_id}','App\Http\Controllers\UserController@show');
Route::get('/event/{event_id}','App\Http\Controllers\EventController@show');
Route::get('/group/{group_id}','App\Http\Controllers\GroupController@show');

Route::post('user', 'App\Http\Controllers\UserController@store');
Route::post('user_event', 'App\Http\Controllers\UserEventController@store');
