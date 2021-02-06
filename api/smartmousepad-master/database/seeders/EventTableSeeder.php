<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class EventTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('event')->insert([
          "event_id" => 1,
          "start_time" => "2017-06-07 09:39:31",
          "end_time" => '2017-06-07 09:39:32',
      ]);
      DB::table('event')->insert([
          "event_id" => 2,
          "start_time" => "2017-06-07 09:39:31",
          "end_time" => "2017-06-07 09:39:31",
      ]);

      DB::table('event')->insert([
          "event_id" => 3,
          "start_time" => "2017-06-07 09:39:31",
          "end_time" => "2017-06-07 09:39:31",
      ]);

      DB::table('event')->insert([
          "event_id" => 4,
          "start_time" => "2017-06-07 09:39:31",
          "end_time" => "2017-06-07 09:39:31",
      ]);
    }
}
