<?php
  
function shuttle_job_application_form($form, &$form_state, $args) {
  $job = node_load($args);
  $title = $job->title;
  if ($description = field_get_items('node', $job, 'field_job_description')) {
    $description = $description[0]['value'];
  }
  if ($qualification = field_get_items('node', $job, 'field_qualification')) {
    $qualification = $qualification[0]['value'];
  }
  if ($position_types = field_get_items('node', $job, 'field_position_types')) {
    $position_types = $position_types[0]['tid'];
  }
  
  
  $form = array();
  
  /* job detail */
  $form['job_detail']['title_content'] = array(
    '#markup' => check_markup($title),
    '#attributes' => array('class'=>'label'),
  );
  $form['job_detail']['description'] = array(
    '#markup' => check_markup('Description:'),
    '#attributes' => array('class'=>'label'),
  );
  $form['job_detail']['description-content'] = array(
    '#markup' => check_markup($description),
    '#attributes' => array('class'=>'job-description'),
  );
  /* application form */
  $form['application_form']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name: '),
  );
  $form['application_form']['coverletter'] = array(
    '#type' => 'textarea',
    '#title' => t('Cover Letter: '),
    '#cols' => 60,
    '#rows' => 10,
  );
  $form['application_form']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone: '),
  );
  $form['application_form']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail: '),
  );
  $form['application_form']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City: '),
  );
  $form['application_form']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State: '),
  );
  $form['application_form']['apply'] = array(
    '#type' => 'submit',
    '#value' => 'Apply to this job'
  );
  
  return $form;
}
function shuttle_job_application_form_validate($form, &$form_state) {
  if ($form_state['values']['name'] == NULL) {
    form_set_error('name', t("Name field must be filled."));
  }
  if ($form_state['values']['coverletter'] == NULL) {
    form_set_error('coverletter', t("Coverletter field must be filled."));
  }
  if ($form_state['values']['email'] == NULL) {
    form_set_error('email', t("E-mail field must be filled."));
  }
  if ($form_state['values']['phone'] == NULL) {
    form_set_error('phone', t("Phone field must be filled."));
  }
  if ($form_state['values']['city'] == NULL) {
    form_set_error('city', t("City field must be filled."));
  }
  if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', t("E-mail format error."));
  }
}
function shuttle_job_application_form_submit($form, &$form_state) {
  $name = $form_state['values']['name'];
  $coverletter = $form_state['values']['coverletter'];
  $email = $form_state['values']['email'];
  $phone = $form_state['values']['phone'];
  $city = $form_state['values']['city'];
  $state = $form_state['values']['state'];
  
}