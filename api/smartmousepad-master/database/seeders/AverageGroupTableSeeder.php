<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class AverageGroupTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('average_group')->insert([
          "group_id" => 1,
          "datetime" => "2017-06-07 09:39:31",
          "group_average" => 0.4,
      ]);
      DB::table('average_group')->insert([
          "group_id" => 2,
          "datetime" => "2017-06-07 09:39:31",
          "group_average" => 0.6,
      ]);
      DB::table('average_group')->insert([
          "group_id" => 3,
          "datetime" => "2017-06-07 09:39:31",
          "group_average" => 0.4,
      ]);
      DB::table('average_group')->insert([
          "group_id" => 4,
          "datetime" => "2017-06-07 09:39:31",
          "group_average" => 0.8,
      ]);
      DB::table('average_group')->insert([
          "group_id" => 5,
          "datetime" => "2017-06-07 09:39:31",
          "group_average" => 0.8,
      ]);
    }
}
