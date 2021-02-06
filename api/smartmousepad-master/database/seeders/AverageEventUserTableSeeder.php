<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class AverageEventUserTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('average_event_user')->insert([
          "user_id" => 1,
          "event_id" => 1,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.6,
      ]);
      DB::table('average_event_user')->insert([
          "user_id" => 1,
          "event_id" => 2,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.2,
      ]);
      DB::table('average_event_user')->insert([
          "user_id" => 1,
          "event_id" => 3,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.5,
      ]);
      DB::table('average_event_user')->insert([
          "user_id" => 1,
          "event_id" => 4,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.9,
      ]);
      DB::table('average_event_user')->insert([
          "user_id" => 2,
          "event_id" => 1,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.7,
      ]);
      DB::table('average_event_user')->insert([
          "user_id" => 3,
          "event_id" => 1,
          "datetime" => "2017-06-07 09:39:31",
          "event_average" => 0.8,
      ]);
    }
}
