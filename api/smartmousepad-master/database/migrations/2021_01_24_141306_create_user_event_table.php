<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateUserEventTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('user_event', function (Blueprint $table) {
          $table->integer('user_id')->unsigned();
          $table->foreign("user_id")->references("user_id")->on("user");
          $table->integer('event_id')->unsigned();
          $table->foreign("event_id")->references("event_id")->on("event");
          $table->double('event_score');
          $table->datetime("datetime")->nullable();
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
        $table->dropForeign('user_event_user_id_foreign');
        $table->dropForeign('user_event_event_id_foreign');
      });
      Schema::dropIfExists('user_event');
    }
}
