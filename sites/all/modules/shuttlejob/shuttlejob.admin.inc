<?php

/*
  functions to respond to user action
*/
function shuttle_job_dashboard() {
  $dashboard_item = array(
    array('title' => t('Jobs'), 'href' => l(t('Jobs'), 'admin/shuttle_job/jobs'), 'localized_options' => array(), 'description' => ''),
    array('title' => t('Applications'), 'href' => l(t('Applications'), 'admin/shuttle_job/applications'), 'localized_options' => array(), 'description' => ''),
  );
  $output = theme('shuttle_job_dashboard', array('content' => $dashboard_item));
  
  return $output;
}

function shuttle_job_list() {
  $build['add_job'] = drupal_get_form('shuttle_job_add_link_form');
  $build['search'] = drupal_get_form('shuttle_job_search_form');
  $build['list'] = drupal_get_form('shuttle_job_list_form');
  
  return $build;
}

function shuttle_job_list_form() {
  $admin_access = user_access('administer shuttlejob');

  // Build the sortable table header.
  $header = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'position_types' => t('Position Type'),
  );
  $header['operations'] = array('data' => t('Operations'));

  $query = db_select('node', 'n')->condition('n.type', 'Job', '=')->extend('PagerDefault')->extend('TableSort');
  //node_build_filter_query($query);

  $nids = $query
    ->fields('n',array('nid'))
    ->limit(25)
    ->addTag('node_access')
    ->execute()
    ->fetchCol();
  $nodes = node_load_multiple($nids);

  // Prepare the list of nodes.
  $destination = drupal_get_destination();
  $options = array();
  foreach ($nodes as $node) {
    if ($position_type = field_get_items('node', $node, 'field_position_types')) {
      $position_type = $position_type[0]['tid'];
      $position_type = taxonomy_term_load($position_type);
      $position_type = $position_type->name;
    }
    $options[$node->nid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $node->title,
          '#href' => 'node/' . $node->nid,
          '#suffix' => ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed))),
        ),
      ),
      'position_types' => $position_type,
      /*
      'type' => check_plain(node_type_get_name($node)),
      'author' => theme('username', array('account' => $node)),
      'status' => $node->status ? t('published') : t('not published'),
      'changed' => format_date($node->changed, 'short'),
      */
    );
    // Build a list of all the accessible operations for the current node.
    $operations = array();
    if (node_access('update', $node)) {
      $operations['edit'] = array(
        'title' => t('edit'),
        'href' => 'node/' . $node->nid . '/edit',
        'query' => $destination,
      );
    }
    if (node_access('delete', $node)) {
      $operations['delete'] = array(
        'title' => t('delete'),
        'href' => 'node/' . $node->nid . '/delete',
        'query' => $destination,
      );
    }
    $options[$node->nid]['operations'] = array();
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#theme' => 'links__node_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }

  $form['nodes'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $options,
    '#empty' => t('No content available.'),
  );

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

function shuttle_job_search_form() {
  $form = array();
  
  return $form;
}

function shuttle_job_add_link_form() {
  $form['actions']['add_job'] = array(
    '#markup' => l(t('Add job'), 'node/add/job'),
  );  
  
  return $form;
}

/*
  edit job
*/
function shuttle_job_edit_form($form, &$form_state, $args) {
  $form = array();
  
  return confirm_form($form,
    t('Edit and save shuttle job.'),
    "admin/shuttle_job/jobs",
    t(''),
    t('Save'),
    t('Cancel')
  );
}
function shuttle_job_edit_form_validate($form, &$form_state) {
  
}
function shuttle_job_edit_form_submit($form, &$form_state) {
  
}

function shuttle_job_delete_confirm($form, &$form_state, $args) {
  $form['#args'] = $args;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['id'] = array('#type' => 'value', '#value' => $args);
  
  return confirm_form($form,
    t('Are you sure?'),
    "admin/shuttle_job/jobs",
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function shuttle_job_delete_confirm_submit($form, &$form_state) {
  /*$id = $form_state['values']['id'];
  $query = "DELETE FROM {groupon_voucher_code_data_model} WHERE id=$id";
  $result = db_query($query);*/
  
  if ($result) {
    drupal_goto("admin/shuttle_job/jobs");
  } else {
    form_set_error('shuttle_job_delete_confirm', t("Failed to delete."));
  }
}

function shuttle_application_list() {
  
}


/*
  theme functions
*/
function theme_shuttle_job_dashboard($variables) {
  $content = $variables['content'];
  $output = '';

  if (!empty($content)) {
    $class = 'admin-list';
    if ($compact = system_admin_compact_mode()) {
      $class .= ' compact';
    }
    $output .= '<dl class="' . $class . '">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
      if (!$compact && isset($item['description'])) {
        $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
      }
    }
    $output .= '</dl>';
  }
  return $output;
}

