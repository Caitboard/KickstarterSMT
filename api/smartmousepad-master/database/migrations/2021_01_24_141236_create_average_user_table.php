<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAverageUserTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('average_user', function (Blueprint $table) {
            $table->integer('user_id')->unsigned();
            $table->foreign("user_id")->references("user_id")->on("user");
            $table->datetime("datetime")->nullable();
            $table->double("user_average");
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
      Schema::table('average_user', function($table){
        $table->dropForeign('average_user_user_id_foreign');
      });
      Schema::dropIfExists('average_user');
    }
}
