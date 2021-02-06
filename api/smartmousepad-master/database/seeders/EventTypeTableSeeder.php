<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class EventTypeTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('event_type')->insert([
          "event_id" => 1,
          "event_name" => "Wandelen",
          "event_description" => "",
      ]);

      DB::table('event_type')->insert([
          "event_id" => 2,
          "event_name" => "Drinken",
          "event_description" => "",
      ]);

      DB::table('event_type')->insert([
          "event_id" => 3,
          "event_name" => "Bewegen",
          "event_description" => "",
      ]);

      DB::table('event_type')->insert([
          "event_id" => 4,
          "event_name" => "Lunchen",
          "event_description" => "",
      ]);
    }
}
