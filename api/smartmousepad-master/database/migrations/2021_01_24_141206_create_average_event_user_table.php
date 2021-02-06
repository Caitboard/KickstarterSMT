<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAverageEventUserTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('average_event_user', function (Blueprint $table) {
            $table->integer('user_id')->unsigned();
            $table->foreign("user_id")->references("user_id")->on("user");
            $table->integer('event_id')->unsigned();
            $table->foreign("event_id")->references("event_id")->on("event");
            $table->datetime("datetime")->nullable();
            $table->double("event_average");
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
      Schema::table('user_event', function($table){
        $table->dropForeign('average_event_user_user_id_foreign');
        $table->dropForeign('average_event_user_event_id_foreign');
      });
      Schema::dropIfExists('average_event_user');
    }
}
