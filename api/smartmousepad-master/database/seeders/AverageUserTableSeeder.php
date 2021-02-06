<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class AverageUserTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('average_user')->insert([
          "user_id" => 1,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
      DB::table('average_user')->insert([
          "user_id" => 2,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
      DB::table('average_user')->insert([
          "user_id" => 3,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
      DB::table('average_user')->insert([
          "user_id" => 4,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
      DB::table('average_user')->insert([
          "user_id" => 5,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
      DB::table('average_user')->insert([
          "user_id" => 6,
          "datetime" => "2017-06-07 09:39:31",
          "user_average" => 0.3,
      ]);
    }
}
