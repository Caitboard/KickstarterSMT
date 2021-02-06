<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use DB;

class UserTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
      DB::table('user')->insert([
          "user_id" => 1,
          "group_id" => 1,
          "first_name" => "Robert",
          "last_name" => "Paardekooper",
          "member_nr" => 1,
      ]);
      DB::table('user')->insert([
          "user_id" => 2,
          "group_id" => 1,
          "first_name" => "Teus",
          "last_name" => "Kamerling",
          "member_nr" => 2,
      ]);
      DB::table('user')->insert([
          "user_id" => 3,
          "group_id" => 1,
          "first_name" => "Caitlin",
          "last_name" => "de Rooij",
          "member_nr" => 3,
      ]);
      DB::table('user')->insert([
          "user_id" => 4,
          "group_id" => 1,
          "first_name" => "John",
          "last_name" => "Roeloffs",
          "member_nr" => 4,
      ]);
      DB::table('user')->insert([
          "user_id" => 5,
          "group_id" => 2,
          "first_name" => "Bart",
          "last_name" => "Klomp",
          "member_nr" => 1,
      ]);
      DB::table('user')->insert([
          "user_id" => 6,
          "group_id" => 2,
          "first_name" => "Bram",
          "last_name" => "van Woerkens",
          "member_nr" => 2,
      ]);
    }
}
