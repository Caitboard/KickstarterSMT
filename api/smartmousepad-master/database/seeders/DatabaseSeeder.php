<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
      $this->call(GroupTableSeeder::class);
      $this->call(EventTableSeeder::class);
      $this->call(UserTableSeeder::class);
      $this->call(AverageEventUserTableSeeder::class);
      $this->call(AverageUserTableSeeder::class);
      $this->call(AverageGroupTableSeeder::class);
      $this->call(UserEventTableSeeder::class);
      $this->call(EventTypeTableSeeder::class);
        // \App\Models\User::factory(10)->create();
    }
}
