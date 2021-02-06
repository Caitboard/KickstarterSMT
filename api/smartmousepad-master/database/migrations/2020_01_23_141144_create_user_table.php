<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateUserTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('user', function (Blueprint $table) {
          $table->increments("user_id");
          $table->integer('group_id')->unsigned();
          $table->foreign('group_id')->references("group_id")->on("group");
          $table->string('first_name');
          $table->string('last_name');
          $table->integer('member_nr');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
      Schema::table('user', function($table){
        $table->dropForeign('user_group_id_foreign');
      });
      Schema::dropIfExists('user');
    }
}
