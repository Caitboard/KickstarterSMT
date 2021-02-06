<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class GroupTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('group')->insert([
        "group_id" => 1,
        "group_name" => "Groep 1",
      ]);

      DB::table('group')->insert([
        "group_id" => 2,
        "group_name" => "Groep 2",
      ]);

      DB::table('group')->insert([
        "group_id" => 3,
        "group_name" => "Groep 3",
      ]);

      DB::table('group')->insert([
        "group_id" => 4,
        "group_name" => "Groep 4",
      ]);

      DB::table('group')->insert([
        "group_id" => 5,
        "group_name" => "Groep 5",
      ]);
      
      DB::table('group')->insert([
        "group_id" => 6,
        "group_name" => "Groep 6",
      ]);

    }
}
